#include "associarwindow.h"
#include "ui_associarwindow.h"

AssociarWindow::AssociarWindow(int i,int j,QList<int> aux,QList<int> a,QList<int> b,QList<int> c,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssociarWindow)
{
    ui->setupUi(this);

    indexAlbum = i;
    indexPagina = j;
    indexFoto = aux;

    listaIndicesAlbum = a;
    listaIndicesPagina = b;
    listaIndicesFoto = c;

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listWidget_2->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->pushButton_4->setEnabled(false);

    refreshListWidget();
    refreshListWidget2();;


}
//=========================================================================================
AssociarWindow::~AssociarWindow()
{
    delete ui;
}
//=========================================================================================
void AssociarWindow::on_pushButton_4_clicked()
{
    if(ui->listWidget->selectedItems().count()==1)
    {
        int indice = ui->listWidget->currentRow();
        Perfil p(indice,0);
        p.exec();
    }
}
//=========================================================================================
void AssociarWindow::on_pushButton_3_clicked()
{
    NovoPerfil np;
    np.exec();
    refreshListWidget();
    ui->pushButton->setEnabled(true);
    F.escreverPessoas(ListaPessoa);
}
//=========================================================================================
void AssociarWindow::refreshListWidget()
{
    ui->listWidget->clear();

    for(int i=0; i<ListaPessoa.count(); i++)
    {
        QListWidgetItem *itm = new QListWidgetItem();
        itm->setText(ListaPessoa.at(i)->getNomePessoa());
        ui->listWidget->addItem(itm);
    }
}
//=========================================================================================
void AssociarWindow::refreshListWidget2()
{
    ui->listWidget_2->clear();

    if(listaIndicesAlbum.isEmpty())
    {
        if(indexPagina==-1)
        {
            for(int p=0; p<ListaAlbum.at(indexAlbum)->ListaPessoas.count();p++)
            {
                QListWidgetItem *itm = new QListWidgetItem();
                itm->setText(ListaAlbum.at(indexAlbum)->ListaPessoas.at(p)->getNomePessoa());
                ui->listWidget_2->addItem(itm);
            }
        }
        else
        {
            if(indexFoto.count()==0)
            {
                for(int p=0; p<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.count();p++)
                {
                    QListWidgetItem *itm = new QListWidgetItem();
                    itm->setText(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.at(p)->getNomePessoa());
                    ui->listWidget_2->addItem(itm);
                }
            }
            else
            {

                    QSet<Pessoa *> intersection;

                    intersection = ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto.at(0))->ListaPessoas.toSet();

                    for(int p=1; p<indexFoto.count(); p++)
                    {
                        intersection.intersect(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto.at(p))->ListaPessoas.toSet());
                    }

                    for(int l=0; l<intersection.toList().count();l++)
                    {
                        QListWidgetItem *itm = new QListWidgetItem();
                        itm->setText(intersection.toList().at(l)->getNomePessoa());
                        ui->listWidget_2->addItem(itm);
                    }


            }
        }
    }
    else
    {
        QSet<Pessoa *> intersection;

        intersection = ListaAlbum.at(listaIndicesAlbum.at(0))->ListaPagina.at(listaIndicesPagina.at(0))->ListaFotos.at(listaIndicesFoto.at(0))->ListaPessoas.toSet();

        for(int p=1; p<listaIndicesAlbum.count(); p++)
        {
            intersection.intersect(ListaAlbum.at(listaIndicesAlbum.at(p))->ListaPagina.at(listaIndicesPagina.at(p))->ListaFotos.at(listaIndicesFoto.at(p))->ListaPessoas.toSet());
        }

        for(int l=0; l<intersection.toList().count();l++)
        {
            QListWidgetItem *itm = new QListWidgetItem();
            itm->setText(intersection.toList().at(l)->getNomePessoa());
            ui->listWidget_2->addItem(itm);
        }
    }


}
//=========================================================================================
void AssociarWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(ui->listWidget->selectedItems().count()==1)
    {
        ui->pushButton_4->setEnabled(true);
    }
    else
    {
        ui->pushButton_4->setEnabled(false);
    }

}
//=========================================================================================
void AssociarWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    if(ui->listWidget_2->selectedItems().count()>0)
    {
        ui->pushButton_2->setEnabled(true);
    }

}
//=========================================================================================
void AssociarWindow::on_pushButton_clicked()
{
    if(listaIndicesAlbum.isEmpty())
    {
        QList<QListWidgetItem*> items = ui->listWidget->selectedItems();

        foreach(QListWidgetItem * item, items)
        {
            bool teste = false;

            if(indexPagina==-1)
            {
                for(int p=0; p<ListaPessoa.count();p++)
                {
                    if(ListaPessoa.at(p)->getNomePessoa()==item->text())
                    {
                        if(!ListaAlbum.at(indexAlbum)->ListaPessoas.contains(ListaPessoa.at(p)))
                        {
                            teste = true;
                            ListaAlbum.at(indexAlbum)->ListaPessoas.append(ListaPessoa.at(p));

                            for(int i=0; i<ListaAlbum.at(indexAlbum)->ListaPagina.count(); i++)
                            {
                                if(!ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaPessoas.contains(ListaPessoa.at(p)))
                                {
                                    ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaPessoas.append(ListaPessoa.at(p));
                                }

                                for(int j=0; j<ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaFotos.count(); j++)
                                {
                                    if(!ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaFotos.at(j)->ListaPessoas.contains(ListaPessoa.at(p)))
                                    {
                                        ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaFotos.at(j)->ListaPessoas.append(ListaPessoa.at(p));
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(indexFoto.count()==0)
                {
                    for(int p=0; p<ListaPessoa.count();p++)
                    {
                        if(ListaPessoa.at(p)->getNomePessoa()==item->text())
                        {
                            if(!ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.contains(ListaPessoa.at(p)))
                            {
                                teste = true;
                                ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.append(ListaPessoa.at(p));

                                for(int j=0; j<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.count(); j++)
                                {
                                    if(!ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(j)->ListaPessoas.contains(ListaPessoa.at(p)))
                                    {
                                        ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(j)->ListaPessoas.append(ListaPessoa.at(p));
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    for(int p=0; p<ListaPessoa.count();p++)
                    {
                        if(ListaPessoa.at(p)->getNomePessoa()==item->text())
                        {
                            for(int j=0; j<indexFoto.count(); j++)
                            {
                                if(!ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto.at(j))->ListaPessoas.contains(ListaPessoa.at(p)))
                                {
                                    teste = true;
                                    ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto.at(j))->ListaPessoas.append(ListaPessoa.at(p));
                                }
                            }
                        }
                    }
                }
            }

            if(!teste)
            {
                QString texto = item->text();
                texto += " já está associado(a)";

                if(indexPagina==-1)
                {
                    texto += " ao album seleccionado.";
                }
                else
                {
                    if(indexFoto.count()==0)
                    {
                        texto += " à pagina seleccionada.";
                    }
                    else
                    {
                        texto += " a uma das fotos seleccionadas.";
                    }
                }
                QMessageBox::critical(this, "ERRO!", texto);
            }
        }
    }

    else
    {
        QList<QListWidgetItem*> items = ui->listWidget->selectedItems();

        foreach(QListWidgetItem * item, items)
        {
            bool teste2 = false;

            for(int p=0; p<ListaPessoa.count();p++)
            {
                if(ListaPessoa.at(p)->getNomePessoa()==item->text())
                {
                    for(int j=0; j<listaIndicesAlbum.count(); j++)
                    {
                        if(!ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(listaIndicesPagina.at(j))->ListaFotos.at(listaIndicesFoto.at(j))->ListaPessoas.contains(ListaPessoa.at(p)))
                        {
                            teste2 = true;
                            ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(listaIndicesPagina.at(j))->ListaFotos.at(listaIndicesFoto.at(j))->ListaPessoas.append(ListaPessoa.at(p));
                        }
                    }
                }
            }
        }
    }

    refreshListWidget2();

}
//=========================================================================================
void AssociarWindow::on_pushButton_2_clicked()
{
    if(listaIndicesAlbum.isEmpty())
    {
        QList<QListWidgetItem*> items = ui->listWidget_2->selectedItems();

        foreach(QListWidgetItem * item, items)
        {

            if(indexPagina==-1)
            {
                for(int p=0; p<ListaAlbum.at(indexAlbum)->ListaPessoas.count();p++)
                {
                    if(ListaAlbum.at(indexAlbum)->ListaPessoas.at(p)->getNomePessoa()==item->text())
                    {
                        ListaAlbum.at(indexAlbum)->ListaPessoas.removeAt(p);

                        for(int i=0; i<ListaAlbum.at(indexAlbum)->ListaPagina.count(); i++)
                        {
                            for(int j=0; j<ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaPessoas.count(); j++)
                            {
                                if(ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaPessoas.at(j)->getNomePessoa()==item->text())
                                {
                                    ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaPessoas.removeAt(j);

                                    for(int k=0; k<ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaFotos.count();k++)
                                    {
                                        for(int l=0; l<ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaFotos.at(k)->ListaPessoas.count();l++)
                                        {
                                            if(ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaFotos.at(k)->ListaPessoas.at(l)->getNomePessoa()==item->text())
                                            {
                                                ListaAlbum.at(indexAlbum)->ListaPagina.at(i)->ListaFotos.at(k)->ListaPessoas.removeAt(l);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(indexFoto.count()==0)
                {
                    for(int f=0; f<ListaAlbum.at(indexAlbum)->ListaPessoas.count(); f++)
                    {
                        if(ListaAlbum.at(indexAlbum)->ListaPessoas.at(f)->getNomePessoa()==item->text())
                        {
                            ListaAlbum.at(indexAlbum)->ListaPessoas.removeAt(f);
                        }
                    }

                    for(int j=0; j<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.count(); j++)
                    {
                        if(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.at(j)->getNomePessoa()==item->text())
                        {
                            ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.removeAt(j);

                            for(int k=0; k<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.count();k++)
                            {
                                for(int l=0; l<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(k)->ListaPessoas.count();l++)
                                {
                                    if(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(k)->ListaPessoas.at(l)->getNomePessoa()==item->text())
                                    {
                                        ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(k)->ListaPessoas.removeAt(l);
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    for(int f=0; f<ListaAlbum.at(indexAlbum)->ListaPessoas.count(); f++)
                    {
                        if(ListaAlbum.at(indexAlbum)->ListaPessoas.at(f)->getNomePessoa()==item->text())
                        {
                            ListaAlbum.at(indexAlbum)->ListaPessoas.removeAt(f);
                        }
                    }

                    for(int f=0; f<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.count(); f++)
                    {
                        if(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.at(f)->getNomePessoa()==item->text())
                        {
                            ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.removeAt(f);
                        }
                    }

                    for(int i=0; i<indexFoto.count(); i++)
                    {
                        for(int l=0; l<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto.at(i))->ListaPessoas.count();l++)
                        {
                            if(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto.at(i))->ListaPessoas.at(l)->getNomePessoa()==item->text())
                            {
                                ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto.at(i))->ListaPessoas.removeAt(l);
                            }
                        }
                    }
                }
            }
        }
    }

    else
    {
        QList<QListWidgetItem*> items = ui->listWidget_2->selectedItems();

        foreach(QListWidgetItem * item, items)
        {

            for(int p=0; p<ListaPessoa.count();p++)
            {
                if(ListaPessoa.at(p)->getNomePessoa()==item->text())
                {
                    for(int j=0; j<listaIndicesAlbum.count(); j++)
                    {
                        for(int i=0; i<ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(listaIndicesPagina.at(j))->ListaFotos.at(listaIndicesFoto.at(j))->ListaPessoas.count(); i++)
                        {
                            if(ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(listaIndicesPagina.at(j))->ListaFotos.at(listaIndicesFoto.at(j))->ListaPessoas.at(i)->getNomePessoa()==item->text())
                            {
                                ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(listaIndicesPagina.at(j))->ListaFotos.at(listaIndicesFoto.at(j))->ListaPessoas.removeAt(i);

                                for(int g=0; g<ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPessoas.count(); g++)
                                {
                                    if(ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPessoas.at(g)->getNomePessoa()==item->text())
                                    {
                                        ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPessoas.removeAt(g);

                                        for(int h=0; h<ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.count(); h++)
                                        {
                                            for(int l=0; l<ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(h)->ListaPessoas.count(); l++)
                                            {
                                                if(ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(h)->ListaPessoas.at(l)->getNomePessoa()==item->text())
                                                {
                                                    ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(h)->ListaPessoas.removeAt(l);
                                                }
                                            }
                                        }
                                    }
                                }

                                for(int y=0; y<ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(listaIndicesPagina.at(j))->ListaPessoas.count(); y++)
                                {
                                    if(ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(listaIndicesPagina.at(j))->ListaPessoas.at(y)->getNomePessoa()==item->text())
                                    {
                                        ListaAlbum.at(listaIndicesAlbum.at(j))->ListaPagina.at(listaIndicesPagina.at(j))->ListaPessoas.removeAt(y);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    refreshListWidget2();

}
