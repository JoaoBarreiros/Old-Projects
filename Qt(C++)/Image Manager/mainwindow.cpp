#include "mainwindow.h"
#include "ui_mainwindow.h"
//================================================================================================================================
/*!
 * \brief MainWindow::MainWindow is the defaut constructor of this class.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->fotowidget->setViewMode(QListWidget::IconMode);

    moverPagina = false;
    moverFotos = false;

    ui->fotowidget->setIconSize(QSize(123,123));
    ui->listWidget->setIconSize(QSize(123,123));
    ui->albumwidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->fotowidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->albumwidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenuA(QPoint)));
    connect(ui->fotowidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenuF1(QPoint)));
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenuF2(QPoint)));

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->fotowidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->albumwidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->pessoaWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->fotowidget->hide();
    ui->informacaowidget->hide();

    refreshTreeWidget();

    for(int i=0; i<ListaAlbum.count(); i++)
    {
        for(int j=0; j<ListaAlbum.at(i)->ListaPagina.count(); j++)
        {
            Pagina* atual=ListaAlbum.at(i)->ListaPagina.at(j);
            QString pasta = atual->getPastaPagina();


            QDir directory(pasta);
            QStringList files = directory.entryList(QStringList() << "*.jpg" <<  "*.png" << "*.jpg" << "*.tiff" << "*.svg" << "*.raw" ,QDir::Files);

            for (int s = 0; s < files.size(); s++)
            {
                QFileInfo fileInfo(pasta+"/"+files.at(s));// Meter como atributo da lista Foto
                QString nome = fileInfo.fileName();

                QString localizacao = fileInfo.absoluteFilePath();
                m_pixmap.load(localizacao);

                QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);
                atual->ListaFotos.append(new Foto(nome,localizacao,resolucao,data,fileInfo));
            }
        }
    }
    F.inicializarAssociacoes(ListaAlbum,ListaPessoa);
}
//================================================================================================================================
/*!
 * \brief MainWindow::~MainWindow is the default destructor of this class.
 */
MainWindow::~MainWindow()
{
    delete ui;
}
//================================================================================================================================
/*!
 * \brief MainWindow::addAlbum adds an album to the treewidget
 */
QTreeWidgetItem* MainWindow::addAlbum(Album *atual)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,atual->getNome());
    ui->albumwidget->addTopLevelItem(itm);
    return itm;
}
//================================================================================================================================
/*!
 * \brief MainWindow::addPagetoAlbum adds a page to an album in the treewidget
 */
void MainWindow::addPagetoAlbum(QTreeWidgetItem *itm,Pagina *pagina)
{
    QTreeWidgetItem *itm2 = new QTreeWidgetItem();
    itm2->setText(0,pagina->getNomePagina());
    itm->addChild(itm2);
}
//================================================================================================================================
/*!
 * \brief MainWindow::refreshTreeWidget refreshes the treeWidget that contains both albums and pages
 */
void MainWindow::refreshTreeWidget()
{
    ui->albumwidget->clear();
    QTreeWidgetItem *itm;
    for(int j = 0; j<ListaAlbum.count(); j++)
    {
        itm = MainWindow::addAlbum(ListaAlbum.at(j));
        for(int i = 0; i<ListaAlbum.at(j)->ListaPagina.count(); i++)
        {
            MainWindow::addPagetoAlbum(itm,ListaAlbum.at(j)->ListaPagina.at(i));
        }
    }
}

//================================================================================================================================
void MainWindow::addPhoto(Foto *atual)
{
    //QPixmap *pix = new QPixmap(atual->getFileInfo().absoluteFilePath())
    m_pixmap.load(atual->getFileInfo().absoluteFilePath());
    m_pixmap = m_pixmap.scaled(800, 600).scaled(200, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if(ui->fotowidget->isVisible())
    {
        ui->fotowidget->setSortingEnabled(false);
        ui->fotowidget->insertRow( ui->fotowidget->rowCount());
        ui->fotowidget->setItem( ui->fotowidget->rowCount()-1, 0,new QTableWidgetItem(QIcon(m_pixmap),atual->getNomeFoto()));
        ui->fotowidget->setItem( ui->fotowidget->rowCount()-1, 1,new QTableWidgetItem(atual->getDataFoto()));
        ui->fotowidget->setItem( ui->fotowidget->rowCount()-1, 2,new QTableWidgetItem(atual->getResolucaoFoto()));
        ui->fotowidget->setSortingEnabled(true);
    }
    else if(ui->listWidget->isVisible())
    {
        ui->listWidget->addItem(new QListWidgetItem(QIcon(m_pixmap),NULL));
    }
}
//================================================================================================================================
/*!
 * \brief MainWindow::refreshListWidget refreshes the listwidget that contains photographs in mosaic view
 * \param pagina is the page that is selected
 */
void MainWindow::refreshListWidget(Pagina *pagina)
{
    ui->listWidget->clear();
    for(int i = 0; i<pagina->ListaFotos.count() ;i++)
    {
        addPhoto(pagina->ListaFotos.at(i));
    }
}
//================================================================================================================================
/*!
 * \brief MainWindow::refreshFotoWidget refreshes the tablewidget that contains photographs in list view
 * \param pagina is the page that is selected
 */
void MainWindow::refreshFotoWidget(Pagina *pagina)
{
    ui->fotowidget->setRowCount(0);
    for(int j = 0; j < pagina->ListaFotos.count(); j++)
    {
        addPhoto(pagina->ListaFotos.at(j));
    }
}
//================================================================================================================================
/*!
 * \brief MainWindow::eliminarFotos removes selected photographs
 */
void MainWindow::eliminarFotos()
{
    QMessageBox messageBox(QMessageBox::Question,
                "Remover",
                "De certeza que pretende eliminar este(s) objeto(s)?",
                QMessageBox::Yes | QMessageBox::No,
                           this);
    messageBox.setButtonText(QMessageBox::Yes, "Sim");
    messageBox.setButtonText(QMessageBox::No, "Não");
    if(messageBox.exec() == QMessageBox::No)
        return;
    else
    {
        if(listaIndicesAlbum.isEmpty())
        {
            int indexAlbum = ui->albumwidget->currentIndex().parent().row();
            int indexPagina = ui->albumwidget->currentIndex().row();

            if(ui->fotowidget->isVisible())
            {

                QItemSelection selection( ui->fotowidget->selectionModel()->selection() );

                QList<int> rows;
                foreach( const QModelIndex & index, selection.indexes() )
                {
                   rows.append( index.row() );
                }

                //qSort( rows );
                std::sort(rows.begin(),rows.end());

                int prev = -1;
                for( int i = rows.count() - 1; i >= 0; i -= 1 )
                {
                   int current = rows[i];
                   if( current != prev )
                   {
                       QFile::remove(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(current)->getDirectorioFoto());
                       ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.removeAt(current);
                       prev = current;
                   }
                }

                ui->fotowidget->selectedItems().clear();
                MainWindow::refreshFotoWidget(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina));
            }

            if(ui->listWidget->isVisible())
            {

                QList<QListWidgetItem*> items = ui->listWidget->selectedItems();


                foreach(QListWidgetItem * item, items)
                {

                    int cr = ui->listWidget->row(item);
                    delete ui->listWidget->takeItem(cr);
                    QFile::remove(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(cr)->getDirectorioFoto());
                    ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.removeAt(cr);
                }

                ui->listWidget->selectedItems().clear();
                MainWindow::refreshListWidget(ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina));
            }

        }
        else
        {
            if(ui->fotowidget->isVisible())
            {

                QItemSelection selection( ui->fotowidget->selectionModel()->selection() );

                QList<int> rows;
                foreach( const QModelIndex & index, selection.indexes() )
                {
                   rows.append( index.row() );
                }

                //qSort( rows );
                std::sort(rows.begin(),rows.end());

                int prev = -1;
                for( int i = rows.count() - 1; i >= 0; i -= 1 )
                {
                   int current = rows[i];
                   if( current != prev )
                   {
                       QFile::remove(ListaAlbum.at(listaIndicesAlbum.at(rows.at(i)))->ListaPagina.at(listaIndicesPagina.at(rows.at(i)))->ListaFotos.at(listaIndicesFoto.at(rows.at(i)))->getDirectorioFoto());
                       ListaAlbum.at(listaIndicesAlbum.at(rows.at(i)))->ListaPagina.at(listaIndicesPagina.at(rows.at(i)))->ListaFotos.removeAt(listaIndicesFoto.at(rows.at(i)));
                       prev = current;

                       for(int g=0; g<listaIndicesAlbum.count();g++)
                       {
                           if(listaIndicesAlbum.at(g)==listaIndicesAlbum.at(rows.at(i)))
                           {
                               if(listaIndicesPagina.at(g)==listaIndicesPagina.at(rows.at(i)))
                               {
                                   if(listaIndicesFoto.at(g)>listaIndicesFoto.at(rows.at(i)))
                                   {
                                       listaIndicesFoto[g]=listaIndicesFoto.at(g)-1;
                                   }
                               }
                           }
                       }
                       listaIndicesAlbum.removeAt(rows[i]);
                       listaIndicesPagina.removeAt(rows[i]);
                       listaIndicesFoto.removeAt(rows[i]);
                       ui->fotowidget->removeRow(rows[i]);
                   }
                }

            }

            if(ui->listWidget->isVisible())
            {

                QList<QListWidgetItem*> items = ui->listWidget->selectedItems();


                QList<int> rows;
                foreach( QListWidgetItem * item, items)
                {
                   rows.append( ui->listWidget->row(item) );
                }

                //qSort( rows );
                std::sort(rows.begin(),rows.end());

                int prev = -1;
                for( int i = rows.count() - 1; i >= 0; i -= 1 )
                {
                   int current = rows[i];
                   if( current != prev )
                   {
                       delete ui->listWidget->takeItem(rows[i]);
                       QFile::remove(ListaAlbum.at(listaIndicesAlbum.at(rows[i]))->ListaPagina.at(listaIndicesPagina.at(rows[i]))->ListaFotos.at(listaIndicesFoto.at(rows[i]))->getDirectorioFoto());
                       ListaAlbum.at(listaIndicesAlbum.at(rows[i]))->ListaPagina.at(listaIndicesPagina.at(rows[i]))->ListaFotos.removeAt(listaIndicesFoto.at(rows[i]));

                       for(int g=0; g<listaIndicesAlbum.count();g++)
                       {
                           if(listaIndicesAlbum.at(g)==listaIndicesAlbum.at(rows.at(i)))
                           {
                               if(listaIndicesPagina.at(g)==listaIndicesPagina.at(rows.at(i)))
                               {
                                   if(listaIndicesFoto.at(g)>listaIndicesFoto.at(rows.at(i)))
                                   {
                                       listaIndicesFoto[g]=listaIndicesFoto.at(g)-1;;
                                   }
                               }
                           }
                       }
                       listaIndicesAlbum.removeAt(rows[i]);
                       listaIndicesPagina.removeAt(rows[i]);
                       listaIndicesFoto.removeAt(rows[i]);
                   }
                }
            }
        }
    }
    F.escreverAssociacoes(ListaAlbum,ListaPessoa);
}
//=========================================================================================
/*!
 * \brief MainWindow::eliminarPastaouAlbum deletes the selected page or album. It also deletes every object inside of them.
 */
void MainWindow::eliminarPastaouAlbum()
{
    QMessageBox messageBox(QMessageBox::Question,
                "Remover",
                "De certeza que pretende eliminar este(s) objeto(s)?",
                QMessageBox::Yes | QMessageBox::No,
                           this);
    messageBox.setButtonText(QMessageBox::Yes, "Sim");
    messageBox.setButtonText(QMessageBox::No, "Não");
    if(messageBox.exec() == QMessageBox::No)
        return;
    else
    {
        QMessageBox messageBox2(QMessageBox::Question,
                    "Remover",
                    "Todos os dados dentro deste(s) objeto(s) serão perdidos, pretende continuar?",
                    QMessageBox::Yes | QMessageBox::No,
                               this);
        messageBox2.setButtonText(QMessageBox::Yes, "Sim");
        messageBox2.setButtonText(QMessageBox::No, "Não");
        if(messageBox2.exec() == QMessageBox::No)
            return;
        else
        {
            if(!ui->albumwidget->currentItem()->parent())//Album selecionado
            {
                Album *atual = ListaAlbum.at(ui->albumwidget->currentIndex().row());
                for(int i = 0; i<atual->ListaPagina.count();i++)
                {
                     Pagina *atual2 = atual->ListaPagina.at(i);
                     atual2->ListaFotos.clear();
                }
                atual->ListaPagina.clear();
                QDir(atual->getPasta()).removeRecursively();
                ListaAlbum.removeAt(ui->albumwidget->currentIndex().row());

                F.escreverAlbuns(ListaAlbum);
                F.escreverPaginas(ListaAlbum);

            }
            else//Pagina selecionada
            {
                int indexA = ui->albumwidget->currentIndex().parent().row();
                int indexP = ui->albumwidget->currentIndex().row();

                QDir(ListaAlbum.at(indexA)->ListaPagina.at(indexP)->getPastaPagina()).removeRecursively();
                ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaFotos.clear();
                ListaAlbum.at(indexA)->ListaPagina.removeAt(indexP);

                F.escreverPaginas(ListaAlbum);
            }

        }
    }
    MainWindow::refreshTreeWidget();
    ui->actionNova_Pagina->setEnabled(false);
    ui->actionEditar->setEnabled(false);
    ui->actionAdicionar_Fotografias->setEnabled(false);
    ui->actionAdicionar_Pasta->setEnabled(false);
    ui->actionAssociar_Pessoas->setEnabled(false);
    ui->actionSlideshow->setEnabled(false);

    if(ui->listWidget->isVisible())
    {
        ui->listWidget->clear();
    }
    if(ui->fotowidget->isVisible())
    {
        ui->fotowidget->setRowCount(0);
    }

    F.escreverAssociacoes(ListaAlbum,ListaPessoa);
}
//=========================================================================================
/*!
 * \brief MainWindow::showContextMenuA creates a custom contex menu for the treewidget that contains albums and pages
 * \param pos is the position where the context menu will open
 */
void MainWindow::showContextMenuA(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = ui->albumwidget->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    if(!ui->albumwidget->selectedItems().isEmpty())
    {
        if(!ui->albumwidget->selectedItems().at(0)->parent())//Estamos a selecionar um album
        {
            myMenu.addAction("Nova Pagina",  this, SLOT(on_actionNova_Pagina_triggered()));
            myMenu.addAction("Eliminar Album",  this, SLOT(eliminarPastaouAlbum()));
            myMenu.addAction("Alterar Dados do Album",  this, SLOT(on_actionEditar_triggered()));
            if(moverPagina)
            {
                myMenu.addAction("Mover Página Escolhida para este Álbum", this, SLOT(MoverPaginaParte2()));
            }

            if(moverFotos)
            {
                myMenu.addAction("Mover Fotos Escolhidas para este Álbum", this, SLOT(MoverFotosParte2()));
            }
            if(copiarPagina)
            {
                myMenu.addAction("Copiar Página Escolhida para este Álbum", this, SLOT(CopiarPaginaParte2()));
            }
            if(copiarFotos)
            {
                myMenu.addAction("Copiar Fotos Escolhidas para este Álbum", this, SLOT(CopiarFotosParte2()));
            }


        }
        else //Pagina is selected
        {
            myMenu.addAction("Eliminar Pagina",  this, SLOT(eliminarPastaouAlbum()));
            myMenu.addAction("Copiar Página", this, SLOT(CopiarPaginaParte1()));
            myMenu.addAction("Mover Página", this, SLOT(MoverPaginaParte1()));

            if(moverFotos)
            {
                myMenu.addAction("Mover Fotos Escolhidas para esta Página", this, SLOT(MoverFotosParte2()));
            }
            if(copiarFotos)
            {
                myMenu.addAction("Copiar Fotos Escolhidas para esta Página", this, SLOT(CopiarFotosParte2()));
            }
        }
    }
    else
    {
        myMenu.addAction("Novo Album",  this, SLOT(on_actionNovo_Album_triggered()));
    }


    // Show context menu at handling position
    myMenu.exec(globalPos);
}
//=========================================================================================
/*!
 * \brief MainWindow::showContextMenuF1 creates a custom contex menu for the tablewidget that contains photographs
 * \param pos is the position where the context menu will open
 */
void MainWindow::showContextMenuF1(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = ui->fotowidget->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;

    if(!ui->fotowidget->selectedItems().isEmpty())
    {

        myMenu.addAction("Eliminar foto(s)", this, SLOT(eliminarFotos()));
        myMenu.addAction("Copiar Fotos", this, SLOT(CopiarFotosParte1()));
        myMenu.addAction("Mover Fotos", this, SLOT(MoverFotosParte1()));

    }

    if(listaIndicesAlbum.isEmpty())
    {
        myMenu.addAction("Adicionar Fotos", this, SLOT(on_actionAdicionar_Fotografias_triggered()));
    }

    // Show context menu at handling position

    myMenu.exec(globalPos);
}
//=========================================================================================
void MainWindow::showContextMenuF2(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = ui->listWidget->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;

    if(!ui->listWidget->selectedItems().isEmpty())
    {

        myMenu.addAction("Eliminar foto(s)", this, SLOT(eliminarFotos()));
        myMenu.addAction("Copiar Fotos", this, SLOT(CopiarFotosParte1()));
        myMenu.addAction("Mover Fotos", this, SLOT(MoverFotosParte1()));

    }

    if(listaIndicesAlbum.isEmpty())
    {
        myMenu.addAction("Adicionar Fotos", this, SLOT(on_actionAdicionar_Fotografias_triggered()));
    }

    // Show context menu at handling position

    myMenu.exec(globalPos);
}
//=========================================================================================
/*!
 * \brief MainWindow::on_actionAcerca_triggered opens the about window
 */
void MainWindow::on_actionAcerca_triggered()
{
    //Incompleto
    acercawindow->show();
}
//=========================================================================================
/*!
 * \brief MainWindow::on_actionNovo_Album_triggered opens the create new album window
 */
void MainWindow::on_actionNovo_Album_triggered()
{
    NovoAlbum na;
    na.exec();

    MainWindow::refreshTreeWidget();

    ui->actionNova_Pagina->setEnabled(false);
    ui->actionEditar->setEnabled(false);
    ui->actionAdicionar_Fotografias->setEnabled(false);
    ui->actionAdicionar_Pasta->setEnabled(false);
    ui->actionAssociar_Pessoas->setEnabled(false);
    ui->actionSlideshow->setEnabled(false);

}
//=========================================================================================
/*!
 * \brief MainWindow::on_actionNovo_Album_triggered opens the create new page window
 */
void MainWindow::on_actionNova_Pagina_triggered()
{
    //QString str = ui->albumwidget->currentItem()->
            /*
            ->text(ui->albumwidget->currentColumn());
        int index = 0;


        while(ListaAlbum.at(index) != NULL)
        {
            if(ListaAlbum.at(index)->getNome()== str)
            {
                break;
            }
            index++;
        }
        */
        int index = ui->albumwidget->currentIndex().row();
        NovaPagina *np = new NovaPagina(index,0);
        np->exec();

        MainWindow::refreshTreeWidget();
        ui->actionNova_Pagina->setEnabled(false);
        ui->actionEditar->setEnabled(false);
        ui->actionAdicionar_Fotografias->setEnabled(false);
        ui->actionAdicionar_Pasta->setEnabled(false);
        ui->actionAssociar_Pessoas->setEnabled(false);
        ui->actionSlideshow->setEnabled(false);
}
//=========================================================================================
void MainWindow::on_actionEditar_triggered()
{
    int index = ui->albumwidget->currentIndex().row();
    AlterarAlbum *aa = new AlterarAlbum(index,0);
    aa->exec();
    MainWindow::refreshTreeWidget();
    ui->actionNova_Pagina->setEnabled(false);
    ui->actionEditar->setEnabled(false);
    ui->actionAdicionar_Fotografias->setEnabled(false);
    ui->actionAdicionar_Pasta->setEnabled(false);
    ui->actionAssociar_Pessoas->setEnabled(false);
}
//=========================================================================================
/*!
 * \brief MainWindow::on_actionSlideshow_triggered opens the start slideshow window
 */
void MainWindow::on_actionSlideshow_triggered()
{
    if(!ui->albumwidget->currentItem()->parent())
    {
        int indexA = ui->albumwidget->currentIndex().row();
        Album *atual2 = ListaAlbum.at(indexA);
        SlideShow *ss = new SlideShow(atual2,0);
        ss->exec();
    }
    else
    {
        int indexA = ui->albumwidget->currentIndex().parent().row();
        int indexP = ui->albumwidget->currentIndex().row();
        Pagina *atual = ListaAlbum.at(indexA)->ListaPagina.at(indexP);
        SlideShow *ss = new SlideShow(atual,0);
        ss->exec();
    }

}
//=========================================================================================
/*!
 * \brief MainWindow::on_actionAdicionar_Pasta_triggered adds new photographs to the current page
 */
void MainWindow::on_actionAdicionar_Pasta_triggered()
{
    QString dir;
    int index;

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty())
    {
        index = ui->albumwidget->currentIndex().row();
        ConfiguracaoNiveis cn(index,dir,0);
        cn.exec();
    }
    F.escreverAssociacoes(ListaAlbum,ListaPessoa);
    refreshTreeWidget();
    ui->actionNova_Pagina->setEnabled(false);
    ui->actionEditar->setEnabled(false);
    ui->actionAdicionar_Fotografias->setEnabled(false);
    ui->actionAdicionar_Pasta->setEnabled(false);
    ui->actionAssociar_Pessoas->setEnabled(false);
    ui->actionSlideshow->setEnabled(false);

}
//=========================================================================================
/*!
 * \brief MainWindow::on_actionAdicionar_Pasta_triggered adds new photographs to the current page
 */
void MainWindow::on_actionAdicionar_Fotografias_triggered()
{
      //É possivel adicionar varias imagens ao mesmo tempo
      QStringList files = QFileDialog::getOpenFileNames(
                  this,
                  "Abrir",
                  "C://",
                  "Imagens (*.png *.jpg *.tiff *.svg *.raw)"
                  );
      // Para cada foto: ver nome, criar icone, encontrar data de criação e buscar a resolução

       if(!files.isEmpty())
       {
          if(!ui->albumwidget->currentItem()->parent()) // se o elemento da albumwidget seleccionado for um album
          {
              if (ui->albumwidget->currentItem()->childCount() == 0) // se esse album nao tiver paginas
              {
                  int index = ui->albumwidget->currentIndex().row();
                  NovaPagina *np = new NovaPagina(index,0);
                  int dialogCode = np->exec();
                  if(dialogCode == QDialog::Accepted)
                  {
                      Pagina *atual = ListaAlbum.at(index)->ListaPagina.first();

                      for (int s = 0; s < files.size(); s++)
                      {
                          QFileInfo fileInfo(files.at(s));// Meter como atributo da lista Foto
                          //QPixmap pix(files.at(s));//Meter como atributo da lista Foto
                          m_pixmap.load(files.at(s));
                          QString nome = fileInfo.fileName();
                          QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                          QString data = fileInfo.birthTime().toString(Qt::DefaultLocaleShortDate);

                          QString localizacao = fileInfo.absoluteFilePath();
                          QFile a;
                          QString novaLocalizacao = atual->getPastaPagina();
                          novaLocalizacao+="/";
                          novaLocalizacao+=nome;
                          a.copy(localizacao,novaLocalizacao);
                          atual->ListaFotos.append(new Foto(nome,novaLocalizacao,resolucao,data,fileInfo));

                          for(int j=0; j<atual->ListaPessoas.count(); j++)
                          {
                              atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                          }

                          MainWindow::addPhoto(atual->ListaFotos.last());
                          //F.escreverFotos(ListaAlbum,index,0);
                      }
                  }
                  MainWindow::refreshTreeWidget();

                  ui->actionNova_Pagina->setEnabled(false);
                  ui->actionEditar->setEnabled(false);
                  ui->actionAdicionar_Fotografias->setEnabled(false);
                  ui->actionAdicionar_Pasta->setEnabled(false);
                  ui->actionAssociar_Pessoas->setEnabled(false);
                  ui->actionSlideshow->setEnabled(false);
                  F.escreverAssociacoes(ListaAlbum,ListaPessoa);
              }
              else // se o album tiver paginas
              {
                  int index = ui->albumwidget->currentIndex().row();
                  Pagina *atual = ListaAlbum.at(index)->ListaPagina.first();

                  for (int s = 0; s < files.size(); s++)
                  {
                      QFileInfo fileInfo(files.at(s));// Meter como atributo da lista Foto
                     // QPixmap pix(files.at(s));//Meter como atributo da lista Foto
                      m_pixmap.load(files.at(s));
                      QString nome = fileInfo.fileName();
                      QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                      QString data = fileInfo.birthTime().toString(Qt::DefaultLocaleShortDate);

                      QString localizacao = fileInfo.absoluteFilePath();
                      QFile a;
                      QString novaLocalizacao = atual->getPastaPagina();
                      novaLocalizacao+="/";
                      novaLocalizacao+=nome;
                      a.copy(localizacao,novaLocalizacao);

                      atual->ListaFotos.append(new Foto(nome,novaLocalizacao,resolucao,data,fileInfo));

                      for(int j=0; j<atual->ListaPessoas.count(); j++)
                      {
                          atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                      }

                      MainWindow::addPhoto(atual->ListaFotos.last());
                      //F.escreverFotos(ListaAlbum,index,0);
                  }
                  F.escreverAssociacoes(ListaAlbum,ListaPessoa);
              }

              //MainWindow::refreshTreeWidget();


              ui->actionNova_Pagina->setEnabled(false);
              ui->actionAdicionar_Fotografias->setEnabled(false);
              ui->actionAdicionar_Pasta->setEnabled(false);
              ui->actionSlideshow->setEnabled(false);
              ui->actionEditar->setEnabled(false);
              ui->actionAssociar_Pessoas->setEnabled(false);
          }
          else // Se for Pagina selecionada
          {
              int indexA = ui->albumwidget->currentIndex().parent().row();
              int indexP = ui->albumwidget->currentIndex().row();
              Pagina *atual = ListaAlbum.at(indexA)->ListaPagina.at(indexP);

              for (int s = 0; s < files.size(); s++)
              {
                  QFileInfo fileInfo(files.at(s));// Meter como atributo da lista Foto
                  //QPixmap pix(files.at(s));//Meter como atributo da lista Foto
                  m_pixmap.load(files.at(s));
                  QString nome = fileInfo.fileName();
                  QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                  QString data = fileInfo.birthTime().toString(Qt::DefaultLocaleShortDate);

                  QString localizacao = fileInfo.absoluteFilePath();
                  QFile a;
                  QString novaLocalizacao = atual->getPastaPagina();
                  novaLocalizacao+="/";
                  novaLocalizacao+=nome;
                  a.copy(localizacao,novaLocalizacao);

                  atual->ListaFotos.append(new Foto(nome,novaLocalizacao,resolucao,data,fileInfo));

                  for(int j=0; j<atual->ListaPessoas.count(); j++)
                  {
                      atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                  }

                  MainWindow::addPhoto(atual->ListaFotos.last());
                  //F.escreverFotos(ListaAlbum,indexA,indexP);
              }
              F.escreverAssociacoes(ListaAlbum,ListaPessoa);
              ui->actionNova_Pagina->setEnabled(false);
              ui->actionAdicionar_Fotografias->setEnabled(true);
              ui->actionAdicionar_Pasta->setEnabled(false);

          }
       }
       if(ui->fotowidget->isVisible())
       {
           ui->fotowidget->resizeColumnToContents(2);
           ui->fotowidget->resizeColumnToContents(1);
           ui->fotowidget->resizeColumnToContents(0);
       }
}
//=========================================================================================
/*!
 * \brief MainWindow::on_albumwidget_itemClicked diplays information about the selected item
 * \param item can refer either to an album or a page
 * \param column by default should be 0
 */
void MainWindow::on_albumwidget_itemClicked(QTreeWidgetItem *item, int column)
{
    listaIndicesAlbum.clear();
    listaIndicesPagina.clear();
    listaIndicesFoto.clear();
    calcularDatas();
    ui->informacaowidget->show();
    ui->actionAdicionar_Fotografias->setEnabled(true);
    ui->actionAssociar_Pessoas->setEnabled(true);
    if(!item->parent())
    {
        ui->actionNova_Pagina->setEnabled(true);
        ui->actionEditar->setEnabled(true);
        ui->actionAdicionar_Pasta->setEnabled(true);
        ui->actionSlideshow->setEnabled(true);
        int index = ui->albumwidget->currentIndex().row();


        ui->pessoaWidget->clear();
        for(int i=0; i<ListaAlbum.at(index)->ListaPessoas.count(); i++)
        {
            QListWidgetItem *itm = new QListWidgetItem();
            itm->setText(ListaAlbum.at(index)->ListaPessoas.at(i)->getNomePessoa());
            ui->pessoaWidget->addItem(itm);
        }

        if(!ui->fotowidget->isHidden())
        {
            ui->fotowidget->setRowCount(0);
        }
        else
        {
            ui->listWidget->clear();
        }

        ui->informacaowidget->clear();
        ui->informacaowidget->addItem(new QListWidgetItem("Album: "+ListaAlbum.at(index)->getNome()));
        ui->informacaowidget->addItem(new QListWidgetItem("Tipo: "+ListaAlbum.at(index)->getTipo()));
        ui->informacaowidget->addItem(new QListWidgetItem("Descrição: "+ListaAlbum.at(index)->getDescricao()));
        ui->informacaowidget->addItem(new QListWidgetItem("Data de Início: "+ListaAlbum.at(index)->getDataInicioAlbum().toString("dd-MM-yyyy")));
        ui->informacaowidget->addItem(new QListWidgetItem("Data de Fim: "+ListaAlbum.at(index)->getDataFimAlbum().toString("dd-MM-yyyy")));

    }
    else
    {
        ui->actionNova_Pagina->setEnabled(false);
        ui->actionEditar->setEnabled(false);
        ui->actionSlideshow->setEnabled(true);
        ui->actionAdicionar_Pasta->setEnabled(false);
        int indexA = ui->albumwidget->currentIndex().parent().row();
        int indexP = ui->albumwidget->currentIndex().row();
        Pagina *atual = ListaAlbum.at(indexA)->ListaPagina.at(indexP);

        ui->pessoaWidget->clear();
        for(int i=0; i<ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaPessoas.count(); i++)
        {
            QListWidgetItem *itm = new QListWidgetItem();
            itm->setText(ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaPessoas.at(i)->getNomePessoa());
            ui->pessoaWidget->addItem(itm);
        }


        ui->informacaowidget->clear();
        ui->informacaowidget->addItem(new QListWidgetItem("Pagina: "+atual->getNomePagina()));
        ui->informacaowidget->addItem(new QListWidgetItem("Tipo: "+atual->getTipoDePagina()));
        ui->informacaowidget->addItem(new QListWidgetItem("Descrição: "+atual->getDescricaoPagina()));
        ui->informacaowidget->addItem(new QListWidgetItem("Data de Início: "+atual->getDataInicioPagina().toString("dd-MM-yyyy")));
        ui->informacaowidget->addItem(new QListWidgetItem("Data de Fim: "+atual->getDataFimPagina().toString("dd-MM-yyyy")));

        if(!ui->fotowidget->isHidden())
        {
            MainWindow::refreshFotoWidget(atual);
        }
        else
        {
            MainWindow::refreshListWidget(atual);
        }

    }

}
//=========================================================================================
/*!
 * \brief MainWindow::on_fotowidget_itemDoubleClicked diplays the photograph in a bigger scale
 * \param item is the selected photograph
 */
void MainWindow::on_fotowidget_itemDoubleClicked(QTableWidgetItem *item)
{
    if(listaIndicesAlbum.isEmpty())
    {
        if(!ui->albumwidget->selectedItems().isEmpty())
        {
            if(!ui->albumwidget->selectedItems().at(0)->parent())
            {
                return;
            }
            else
            {
                int indexA = ui->albumwidget->currentIndex().parent().row();
                int indexP = ui->albumwidget->currentIndex().row();
                int indexF = ui->fotowidget->currentRow();

                Foto *atual = ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaFotos.at(indexF);

                ui->pessoaWidget->clear();
                for(int i=0; i<atual->ListaPessoas.count(); i++)
                {
                    QListWidgetItem *itm = new QListWidgetItem();
                    itm->setText(atual->ListaPessoas.at(i)->getNomePessoa());
                    ui->pessoaWidget->addItem(itm);
                }

                //QPixmap *foto = new QPixmap(atual->getFileInfo().absoluteFilePath());
                ImageViewer *im = new ImageViewer(atual->getFileInfo().absoluteFilePath(),0);
                im->setAttribute(Qt::WA_DeleteOnClose);
                im->exec();
            }
        }
    }
    else
    {
        int indexF = ui->fotowidget->currentRow();

        Foto *atual = ListaAlbum.at(listaIndicesAlbum.at(indexF))->ListaPagina.at(listaIndicesPagina.at(indexF))->ListaFotos.at(listaIndicesFoto.at(indexF));

        ui->pessoaWidget->clear();
        for(int i=0; i<atual->ListaPessoas.count(); i++)
        {
            QListWidgetItem *itm = new QListWidgetItem();
            itm->setText(atual->ListaPessoas.at(i)->getNomePessoa());
            ui->pessoaWidget->addItem(itm);
        }

        //QPixmap *foto = new QPixmap(atual->getFileInfo().absoluteFilePath());
        ImageViewer *im = new ImageViewer(atual->getFileInfo().absoluteFilePath(),0);
        im->setAttribute(Qt::WA_DeleteOnClose);
        im->exec();

    }

    //imageviewer->show();
    //se pagina selecionada:

}
//=========================================================================================
/*!
 * \brief MainWindow::on_listWidget_itemDoubleClicked diplays the photograph in a bigger scale
 * \param item is the selected photograph
 */
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(listaIndicesAlbum.isEmpty())
    {
        if(!ui->albumwidget->selectedItems().isEmpty())
        {
            if(!ui->albumwidget->selectedItems().at(0)->parent())
            {
                return;
            }
            else
            {
                int indexA = ui->albumwidget->currentIndex().parent().row();
                int indexP = ui->albumwidget->currentIndex().row();
                int indexF = ui->listWidget->currentIndex().row();
                Foto *atual = ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaFotos.at(indexF);

                ui->pessoaWidget->clear();
                for(int i=0; i<atual->ListaPessoas.count(); i++)
                {
                    QListWidgetItem *itm = new QListWidgetItem();
                    itm->setText(atual->ListaPessoas.at(i)->getNomePessoa());
                    ui->pessoaWidget->addItem(itm);
                }

                //QPixmap *foto = new QPixmap(atual->getFileInfo().absoluteFilePath());
                ImageViewer *im = new ImageViewer(atual->getFileInfo().absoluteFilePath(),0);
                im->setAttribute(Qt::WA_DeleteOnClose);
                im->exec();
            }
        }
    }

   else
   {
        int indexF = ui->listWidget->currentIndex().row();
        Foto *atual = ListaAlbum.at(listaIndicesAlbum.at(indexF))->ListaPagina.at(listaIndicesPagina.at(indexF))->ListaFotos.at(listaIndicesFoto.at(indexF));

        ui->pessoaWidget->clear();
        for(int i=0; i<atual->ListaPessoas.count(); i++)
        {
            QListWidgetItem *itm = new QListWidgetItem();
            itm->setText(atual->ListaPessoas.at(i)->getNomePessoa());
            ui->pessoaWidget->addItem(itm);
        }

        //QPixmap *foto = new QPixmap(atual->getFileInfo().absoluteFilePath());
        ImageViewer *im = new ImageViewer(atual->getFileInfo().absoluteFilePath(),0);
        im->setAttribute(Qt::WA_DeleteOnClose);
        im->exec();

   }

}
//=========================================================================================
/*
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}
//=========================================================================================
void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        qDebug() << "Dropped file:" << fileName;
    }
}
*/
//=========================================================================================
/*!
 * \brief MainWindow::on_vistaListaCompleta_clicked diplays the photographs in a detailed list
 */
void MainWindow::on_vistaListaCompleta_clicked()
{
    if(listaIndicesAlbum.isEmpty())
    {
        if(!ui->albumwidget->selectedItems().isEmpty())
        {
            if(!ui->albumwidget->selectedItems().at(0)->parent())
            {
                return;
            }
            else
            {
                ui->fotowidget->setColumnHidden(1, false);
                ui->fotowidget->setColumnHidden(2, false);
                if(ui->fotowidget->isHidden())
                {
                    int indexA = ui->albumwidget->currentIndex().parent().row();
                    int indexP = ui->albumwidget->currentIndex().row();
                    ui->fotowidget->setHidden(false);
                    ui->listWidget->setHidden(true);
                    MainWindow::refreshFotoWidget(ListaAlbum.at(indexA)->ListaPagina.at(indexP));
                    ui->fotowidget->resizeColumnToContents(2);
                    ui->fotowidget->resizeColumnToContents(1);
                    ui->fotowidget->resizeColumnToContents(0);
                }
            }
        }
    }

    else
    {
        ui->fotowidget->setColumnHidden(1, false);
        ui->fotowidget->setColumnHidden(2, false);
        if(ui->fotowidget->isHidden())
        {
            ui->fotowidget->setHidden(false);
            ui->listWidget->setHidden(true);
            ui->fotowidget->setRowCount(0);

            for(int i=0;i<listaIndicesAlbum.count() ;i++)
            {
                addPhoto(ListaAlbum.at(listaIndicesAlbum.at(i))->ListaPagina.at(listaIndicesPagina.at(i))->ListaFotos.at(listaIndicesFoto.at(i)));
            }
            ui->fotowidget->resizeColumnToContents(2);
            ui->fotowidget->resizeColumnToContents(1);
            ui->fotowidget->resizeColumnToContents(0);
        }

    }


}
//=========================================================================================
/*!
 * \brief MainWindow::on_vistaMosaico_clicked diplays the photographs in a mosaic view
 */
void MainWindow::on_vistaMosaico_clicked()//Necessario otimizar
{
    if(listaIndicesAlbum.isEmpty())
    {
        if(!ui->albumwidget->selectedItems().isEmpty())
        {
            if(!ui->albumwidget->selectedItems().at(0)->parent())
            {
                return;
            }
            else
            {
                int indexA = ui->albumwidget->currentIndex().parent().row();
                int indexP = ui->albumwidget->currentIndex().row();
                ui->fotowidget->setHidden(true);
                ui->listWidget->setHidden(false);
                MainWindow::refreshListWidget(ListaAlbum.at(indexA)->ListaPagina.at(indexP));

            }
        }
    }
    else
    {
        ui->fotowidget->setHidden(true);
        ui->listWidget->setHidden(false);
        ui->listWidget->clear();
        for(int i=0;i<listaIndicesAlbum.count() ;i++)
        {
            addPhoto(ListaAlbum.at(listaIndicesAlbum.at(i))->ListaPagina.at(listaIndicesPagina.at(i))->ListaFotos.at(listaIndicesFoto.at(i)));
        }
    }

}
//=========================================================================================
/*!
 * \brief MainWindow::on_vistaListaSimples_clicked diplays the photographs in a simple view
 */
void MainWindow::on_vistaListaSimples_clicked()
{
    if(listaIndicesAlbum.isEmpty())
    {
        if(!ui->albumwidget->selectedItems().isEmpty())
        {
            if(!ui->albumwidget->selectedItems().at(0)->parent())
            {
                return;
            }
            else
            {
                ui->fotowidget->setColumnHidden(1, true);
                ui->fotowidget->setColumnHidden(2, true);

                if(ui->fotowidget->isHidden())
                {
                    int indexA = ui->albumwidget->currentIndex().parent().row();
                    int indexP = ui->albumwidget->currentIndex().row();
                    ui->fotowidget->setHidden(false);
                    ui->listWidget->setHidden(true);
                    MainWindow::refreshFotoWidget(ListaAlbum.at(indexA)->ListaPagina.at(indexP));
                }
            }
        }
    }
    else
    {
        ui->fotowidget->setColumnHidden(1, true);
        ui->fotowidget->setColumnHidden(2, true);

        if(ui->fotowidget->isHidden())
        {
            ui->fotowidget->setHidden(false);
            ui->listWidget->setHidden(true);
            ui->fotowidget->setRowCount(0);
            for(int i=0;i<listaIndicesAlbum.count() ;i++)
            {
                addPhoto(ListaAlbum.at(listaIndicesAlbum.at(i))->ListaPagina.at(listaIndicesPagina.at(i))->ListaFotos.at(listaIndicesFoto.at(i)));
            }
        }
    }
}
//=========================================================================================
void MainWindow::on_actionAssociar_Pessoas_triggered()
{
    if(!ui->albumwidget->selectedItems().isEmpty())
    {
        if(!ui->albumwidget->currentItem()->parent()) // se o elemento da albumwidget seleccionado for um album
        {
            QList <int> aux;
            QList <int> listaA;
            QList <int> listaP;
            QList <int> listaF;
            int indice = ui->albumwidget->currentIndex().row();
            AssociarWindow aw(indice,-1,aux,listaA,listaP,listaF,0);
            aw.exec();
        }
        else
        {
            int indiceA = ui->albumwidget->currentIndex().parent().row();
            int indiceP = ui->albumwidget->currentIndex().row();

            if(ui->listWidget->isVisible())
            {
                if(ui->listWidget->selectedItems().isEmpty())
                {
                    QList <int> listaA;
                    QList <int> listaP;
                    QList <int> listaF;
                    QList <int> aux;
                    AssociarWindow aw(indiceA,indiceP,aux,listaA,listaP,listaF,0);
                    aw.exec();
                }

                else
                {
                    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
                    QList <int> aux;
                    QList <int> listaA;
                    QList <int> listaP;
                    QList <int> listaF;

                    foreach(QListWidgetItem * item, items)
                    {
                        aux.append(ui->listWidget->row(item));
                    }

                    AssociarWindow aw(indiceA,indiceP,aux,listaA,listaP,listaF,0);
                    aw.exec();
                }

            }
            if(ui->fotowidget->isVisible())
            {
                QItemSelection selection( ui->fotowidget->selectionModel()->selection() );

                if(selection.isEmpty())
                {
                    QList <int> aux;
                    QList <int> listaA;
                    QList <int> listaP;
                    QList <int> listaF;
                    AssociarWindow aw(indiceA,indiceP,aux,listaA,listaP,listaF,0);
                    aw.exec();
                }

                else
                {
                    QList<int> aux;
                    QList <int> listaA;
                    QList <int> listaP;
                    QList <int> listaF;

                    foreach( const QModelIndex & index, selection.indexes() )
                    {
                       aux.append( index.row() );
                    }

                    AssociarWindow aw(indiceA,indiceP,aux,listaA,listaP,listaF,0);
                    aw.exec();

                }

            }

        }

    }

    else
    {
        if(ui->listWidget->isVisible())
        {
            if(ui->listWidget->selectedItems().isEmpty())
            {
                QList <int> aux;
                AssociarWindow aw(-1,-1,aux,listaIndicesAlbum,listaIndicesPagina,listaIndicesFoto,0);
                aw.exec();
            }

            else
            {
                QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
                QList <int> aux;
                QList <int> listaA;
                QList <int> listaP;
                QList <int> listaF;

                foreach(QListWidgetItem * item, items)
                {
                    listaA.append(listaIndicesAlbum.at(ui->listWidget->row(item)));
                    listaP.append(listaIndicesPagina.at(ui->listWidget->row(item)));
                    listaF.append(listaIndicesFoto.at(ui->listWidget->row(item)));
                }

                AssociarWindow aw(-1,-1,aux,listaA,listaP,listaF,0);
                aw.exec();
            }

        }
        if(ui->fotowidget->isVisible())
        {
            QItemSelection selection( ui->fotowidget->selectionModel()->selection() );

            if(selection.isEmpty())
            {
                QList <int> aux;
                AssociarWindow aw(-1,-1,aux,listaIndicesAlbum,listaIndicesPagina,listaIndicesFoto,0);
                aw.exec();
            }

            else
            {
                QList<int> aux;
                QList <int> listaA;
                QList <int> listaP;
                QList <int> listaF;

                foreach( const QModelIndex & index, selection.indexes() )
                {
                    listaA.append(listaIndicesAlbum.at(index.row()));
                    listaP.append(listaIndicesPagina.at(index.row()));
                    listaF.append(listaIndicesFoto.at(index.row()));
                }

                AssociarWindow aw(-1,-1,aux,listaA,listaP,listaF,0);
                aw.exec();

            }
        }
    }

    F.escreverAssociacoes(ListaAlbum,ListaPessoa);

}
//=========================================================================================
void MainWindow::on_pessoaWidget_itemDoubleClicked(QListWidgetItem *item)
{
    for(int i=0; i<ListaPessoa.count(); i++)
    {
        if(ListaPessoa.at(i)->getNomePessoa()==item->text())
        {
            Perfil p(i,0);
            p.exec();
        }
    }
}
//=========================================================================================
void MainWindow::on_fotowidget_itemClicked(QTableWidgetItem *item)
{
    ui->actionAssociar_Pessoas->setEnabled(true);
    if(listaIndicesAlbum.isEmpty())
    {
        if(!ui->albumwidget->selectedItems().isEmpty())
        {
            if(!ui->albumwidget->selectedItems().at(0)->parent())
            {
                return;
            }
            else
            {
                QItemSelection selection( ui->fotowidget->selectionModel()->selection() );
                int indexA = ui->albumwidget->currentIndex().parent().row();
                int indexP = ui->albumwidget->currentIndex().row();
                QList <int> indicesFotos;

                foreach( const QModelIndex & index, selection.indexes() )
                {
                    indicesFotos.append(index.row());
                }

                QSet<Pessoa *> intersection;

                intersection = ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaFotos.at(indicesFotos.first())->ListaPessoas.toSet();


                for(int p=1; p<indicesFotos.count(); p++)
                {
                    intersection.intersect(ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaFotos.at(indicesFotos.at(p))->ListaPessoas.toSet());
                }

                ui->pessoaWidget->clear();

                for(int l=0; l<intersection.toList().count();l++)
                {
                    QListWidgetItem *itm = new QListWidgetItem();
                    itm->setText(intersection.toList().at(l)->getNomePessoa());
                    ui->pessoaWidget->addItem(itm);
                }
            }
        }
    }
    else
    {
        QItemSelection selection( ui->fotowidget->selectionModel()->selection() );

        QList <int> indicesFotos;

        foreach( const QModelIndex & index, selection.indexes() )
        {
            indicesFotos.append(index.row());
        }

        QSet<Pessoa *> intersection;

        intersection = ListaAlbum.at(listaIndicesAlbum.at(indicesFotos.first()))->ListaPagina.at(listaIndicesPagina.at(indicesFotos.first()))->ListaFotos.at(listaIndicesFoto.at(indicesFotos.first()))->ListaPessoas.toSet();


        for(int p=1; p<indicesFotos.count(); p++)
        {
            intersection.intersect(ListaAlbum.at(listaIndicesAlbum.at(indicesFotos.at(p)))->ListaPagina.at(listaIndicesPagina.at(indicesFotos.at(p)))->ListaFotos.at(listaIndicesFoto.at(indicesFotos.at(p)))->ListaPessoas.toSet());
        }

        ui->pessoaWidget->clear();
        for(int l=0; l<intersection.toList().count();l++)
        {
            QListWidgetItem *itm = new QListWidgetItem();
            itm->setText(intersection.toList().at(l)->getNomePessoa());
            ui->pessoaWidget->addItem(itm);
        }

    }
}
//=========================================================================================
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->actionAssociar_Pessoas->setEnabled(true);
    if(listaIndicesAlbum.isEmpty())
    {
        if(!ui->albumwidget->selectedItems().isEmpty())
        {
            if(!ui->albumwidget->selectedItems().at(0)->parent())
            {
                return;
            }
            else
            {
                int indexA = ui->albumwidget->currentIndex().parent().row();
                int indexP = ui->albumwidget->currentIndex().row();

                QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
                QList <int> indicesFotos;

                foreach(QListWidgetItem * item1, items)
                {
                    indicesFotos.append(ui->listWidget->row(item1));
                }

                QSet<Pessoa *> intersection;

                intersection = ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaFotos.at(indicesFotos.first())->ListaPessoas.toSet();


                for(int p=1; p<indicesFotos.count(); p++)
                {
                    intersection.intersect(ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaFotos.at(indicesFotos.at(p))->ListaPessoas.toSet());
                }


                ui->pessoaWidget->clear();
                for(int l=0; l<intersection.toList().count();l++)
                {
                    QListWidgetItem *itm = new QListWidgetItem();
                    itm->setText(intersection.toList().at(l)->getNomePessoa());
                    ui->pessoaWidget->addItem(itm);
                }
            }
        }
    }

    else
    {
        QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
        QList <int> indicesFotos;

        foreach(QListWidgetItem * item1, items)
        {
            indicesFotos.append(ui->listWidget->row(item1));
        }

        QSet<Pessoa *> intersection;

        intersection = ListaAlbum.at(listaIndicesAlbum.at(indicesFotos.first()))->ListaPagina.at(listaIndicesPagina.at(indicesFotos.first()))->ListaFotos.at(listaIndicesFoto.at(indicesFotos.first()))->ListaPessoas.toSet();


        for(int p=1; p<indicesFotos.count(); p++)
        {
            intersection.intersect(ListaAlbum.at(listaIndicesAlbum.at(indicesFotos.at(p)))->ListaPagina.at(listaIndicesPagina.at(indicesFotos.at(p)))->ListaFotos.at(listaIndicesFoto.at(indicesFotos.at(p)))->ListaPessoas.toSet());
        }


        ui->pessoaWidget->clear();
        for(int l=0; l<intersection.toList().count();l++)
        {
            QListWidgetItem *itm = new QListWidgetItem();
            itm->setText(intersection.toList().at(l)->getNomePessoa());
            ui->pessoaWidget->addItem(itm);
        }
    }
}
//=========================================================================================

void MainWindow::on_lineEdit_returnPressed()
{
    QString texto = ui->lineEdit->text();
    if(!texto.isEmpty())
    {
        refreshTreeWidget();
        ui->actionNova_Pagina->setEnabled(false);
        ui->actionEditar->setEnabled(false);
        ui->actionAdicionar_Fotografias->setEnabled(false);
        ui->actionAdicionar_Pasta->setEnabled(false);
        ui->actionAssociar_Pessoas->setEnabled(true);
        ui->actionSlideshow->setEnabled(false);

        listaIndicesAlbum.clear();
        listaIndicesPagina.clear();
        listaIndicesFoto.clear();

        if(ui->listWidget->isVisible())
        {
            ui->listWidget->clear();
        }
        if(ui->fotowidget->isVisible())
        {
            ui->fotowidget->setRowCount(0);
        }

        for(int i=0; i<ListaAlbum.count(); i++)
        {
            for(int j=0; j<ListaAlbum.at(i)->ListaPagina.count(); j++)
            {
                for(int k=0; k<ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.count(); k++)
                {
                    if(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getDataFoto().contains(texto))
                    {

                        addPhoto(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k));
                        listaIndicesAlbum.append(i);
                        listaIndicesPagina.append(j);
                        listaIndicesFoto.append(k);
                    }

                    if(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getNomeFoto().startsWith(texto))
                    {
                        addPhoto(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k));
                        listaIndicesAlbum.append(i);
                        listaIndicesPagina.append(j);
                        listaIndicesFoto.append(k);
                    }

                    for(int l=0; l<ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->ListaPessoas.count();l++)
                    {
                        if(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->ListaPessoas.at(l)->getNomePessoa().startsWith(texto))
                        {
                            addPhoto(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k));
                            listaIndicesAlbum.append(i);
                            listaIndicesPagina.append(j);
                            listaIndicesFoto.append(k);
                        }
                    }
                }
            }
        }
    }
}
//=========================================================================================
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    //QString texto = //ui->lineEdit->text();
    completionList.clear();
    if(!arg1.isEmpty())
    {
        for(int i=0; i<ListaAlbum.count(); i++)
        {
            for(int j=0; j<ListaAlbum.at(i)->ListaPagina.count(); j++)
            {
                for(int k=0; k<ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.count(); k++)
                {
                    if(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getDataFoto().startsWith(arg1))
                    {
                        completionList<<ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getDataFoto();
                    }

                    if(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getNomeFoto().startsWith(arg1))
                    {
                        completionList<<ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getNomeFoto();
                    }

                    for(int l=0; l<ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->ListaPessoas.count();l++)
                    {
                        if(ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->ListaPessoas.at(l)->getNomePessoa().startsWith(arg1))
                        {
                            completionList<<ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->ListaPessoas.at(l)->getNomePessoa();
                        }
                    }
                }
            }
        }
        completionList.removeDuplicates();
        stringCompleter = new QCompleter(completionList,this);
        stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->lineEdit->setCompleter(stringCompleter);
    }
}
//=========================================================================================
void MainWindow::MoverPaginaParte1()
{
    moverPagina=true;
    indiceDeAlbum = ui->albumwidget->currentIndex().parent().row();
    indiceDePagina = ui->albumwidget->currentIndex().row();
}
//=========================================================================================
void MainWindow::CopiarPaginaParte1()
{
    copiarPagina=true;
    indiceDeAlbum = ui->albumwidget->currentIndex().parent().row();
    indiceDePagina = ui->albumwidget->currentIndex().row();
}
//=========================================================================================
void MainWindow::CopiarPaginaParte2()
{
    int albumDestino = ui->albumwidget->currentIndex().row();
    bool teste = true;

    if(ListaAlbum.at(albumDestino)->getTipo() == ListaAlbum.at(indiceDeAlbum)->getTipo() )
    {
        if(albumDestino != indiceDeAlbum)
        {
            for(int i=0; i<ListaAlbum.at(albumDestino)->ListaPagina.count(); i++)
            {
                for(int j=0; j<ListaAlbum.at(indiceDeAlbum)->ListaPagina.count(); j++)
                {
                    if( ListaAlbum.at(albumDestino)->ListaPagina.at(i)->getNomePagina() == ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(j)->getNomePagina() )
                    {
                        teste = false;
                    }
                    if( ListaAlbum.at(albumDestino)->ListaPagina.at(i)->getDescricaoPagina() == ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(j)->getDescricaoPagina() )
                    {
                        teste = false;
                    }
                }

            }
            if(teste)
            {

                ListaAlbum.at(albumDestino)->ListaPagina.append(ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina));
                QFileInfo a( ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina)->getPastaPagina());

                QString nome = a.fileName();
                QString novaPasta = ListaAlbum.at(albumDestino)->getPasta() + "/" + nome;

                QDir b;
                b.mkpath(novaPasta);


                QFile c;
                QString diretorio,nomeFoto;
                for(int i=0; i<ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina)->ListaFotos.count() ;i++)
                {
                    diretorio = ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina)->ListaFotos.at(i)->getDirectorioFoto();
                    nomeFoto = ListaAlbum.at(albumDestino)->ListaPagina.last()->ListaFotos.at(i)->getNomeFoto();
                    ListaAlbum.at(albumDestino)->ListaPagina.last()->ListaFotos.at(i)->setDirectorioFoto(novaPasta +"/"+nomeFoto);
                    c.copy(diretorio,novaPasta+"/"+nomeFoto);
                    ListaAlbum.at(albumDestino)->ListaPagina.last()->ListaFotos.at(i)->setFileInfo(QFileInfo(novaPasta+"/"+nomeFoto));
                }
                ListaAlbum.at(albumDestino)->ListaPagina.last()->setPasta(novaPasta);

                refreshTreeWidget();
                ui->actionNova_Pagina->setEnabled(false);
                ui->actionEditar->setEnabled(false);
                ui->actionAdicionar_Fotografias->setEnabled(false);
                ui->actionAdicionar_Pasta->setEnabled(false);
                ui->actionAssociar_Pessoas->setEnabled(false);

                F.escreverPaginas(ListaAlbum);
                F.escreverAssociacoes(ListaAlbum,ListaPessoa);
            }
            else
            {
                QMessageBox::critical(this, "ERRO!", "A página já existe no álbum seleccionado");
            }
        }
        else
        {
            QMessageBox::critical(this, "ERRO!", "A página já existe no álbum seleccionado");
        }
    }
    else
    {
        QMessageBox::critical(this, "ERRO!", "O tipo de páginas no álbum destino não é compatível com o tipo de página seleccionada");
    }
    copiarPagina=false;
}
//=========================================================================================
void MainWindow::MoverPaginaParte2()
{
    int albumDestino = ui->albumwidget->currentIndex().row();
    bool teste = true;

    if(ListaAlbum.at(albumDestino)->getTipo() == ListaAlbum.at(indiceDeAlbum)->getTipo() )
    {
        if(albumDestino != indiceDeAlbum)
        {
            for(int i=0; i<ListaAlbum.at(albumDestino)->ListaPagina.count(); i++)
            {
                for(int j=0; j<ListaAlbum.at(indiceDeAlbum)->ListaPagina.count(); j++)
                {
                    if( ListaAlbum.at(albumDestino)->ListaPagina.at(i)->getNomePagina() == ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(j)->getNomePagina() )
                    {
                        teste = false;
                    }
                    if( ListaAlbum.at(albumDestino)->ListaPagina.at(i)->getDescricaoPagina() == ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(j)->getDescricaoPagina() )
                    {
                        teste = false;
                    }
                }

            }
            if(teste)
            {

                ListaAlbum.at(albumDestino)->ListaPagina.append(ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina));
                QFileInfo a( ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina)->getPastaPagina());

                QString nome = a.fileName();
                QString novaPasta = ListaAlbum.at(albumDestino)->getPasta() + "/" + nome;

                QDir b;
                b.mkpath(novaPasta);


                QFile c;
                QString diretorio,nomeFoto;
                for(int i=0; i<ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina)->ListaFotos.count() ;i++)
                {
                    diretorio = ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina)->ListaFotos.at(i)->getDirectorioFoto();
                    nomeFoto = ListaAlbum.at(albumDestino)->ListaPagina.last()->ListaFotos.at(i)->getNomeFoto();
                    ListaAlbum.at(albumDestino)->ListaPagina.last()->ListaFotos.at(i)->setDirectorioFoto(novaPasta +"/"+nomeFoto);
                    c.copy(diretorio,novaPasta+"/"+nomeFoto);
                    ListaAlbum.at(albumDestino)->ListaPagina.last()->ListaFotos.at(i)->setFileInfo(QFileInfo(novaPasta+"/"+nomeFoto));
                }
                QDir (ListaAlbum.at(indiceDeAlbum)->ListaPagina.at(indiceDePagina)->getPastaPagina()).removeRecursively();
                ListaAlbum.at(indiceDeAlbum)->ListaPagina.removeAt(indiceDePagina);

                ListaAlbum.at(albumDestino)->ListaPagina.last()->setPasta(novaPasta);

                refreshTreeWidget();
                ui->actionNova_Pagina->setEnabled(false);
                ui->actionEditar->setEnabled(false);
                ui->actionAdicionar_Fotografias->setEnabled(false);
                ui->actionAdicionar_Pasta->setEnabled(false);
                ui->actionAssociar_Pessoas->setEnabled(false);
                ui->actionSlideshow->setEnabled(false);

                F.escreverPaginas(ListaAlbum);
                F.escreverAssociacoes(ListaAlbum,ListaPessoa);



            }
            else
            {
                QMessageBox::critical(this, "ERRO!", "A página já existe no álbum seleccionado");
            }
        }
        else
        {
            QMessageBox::critical(this, "ERRO!", "A página já existe no álbum seleccionado");
        }
    }
    else
    {
        QMessageBox::critical(this, "ERRO!", "O tipo de páginas no álbum destino não é compatível com o tipo de página seleccionada");
    }
    moverPagina=false;
}

//=========================================================================================
void MainWindow::MoverFotosParte1()
{
    if(listaIndicesAlbum.isEmpty())
    {
        indiceAlbumParaMoverFotos = ui->albumwidget->currentIndex().parent().row();
        indicePaginaParaMoverFotos = ui->albumwidget->currentIndex().row();
        indiceFotosParaMoverFotos.clear();

        if(ui->listWidget->isVisible())
        {
            QList<QListWidgetItem*> items = ui->listWidget->selectedItems();

            foreach(QListWidgetItem * item, items)
            {
                indiceFotosParaMoverFotos.append(ui->listWidget->row(item));
            }

        }
        if(ui->fotowidget->isVisible())
        {
            //QItemSelection selection( ui->fotowidget->selectionModel()->selection() );
            QModelIndexList selection = ui->fotowidget->selectionModel()->selectedRows();
            for(int i=0; i< selection.count(); i++)
            {
                QModelIndex index = selection.at(i);
                indiceFotosParaMoverFotos.append( index.row());
            }
        }
    }

    else
    {
        listaIndicesAlbumParaMoverFotos.clear();
        listaIndicesPaginaParaMoverFotos.clear();
        listaIndicesFotoParaMoverFotos.clear();

        if(ui->listWidget->isVisible())
        {
            QList<QListWidgetItem*> items = ui->listWidget->selectedItems();

            foreach(QListWidgetItem * item, items)
            {
                listaIndicesAlbumParaMoverFotos.append( listaIndicesAlbum.at( ui->listWidget->row(item) ) );
                listaIndicesPaginaParaMoverFotos.append( listaIndicesPagina.at( ui->listWidget->row(item) ) );
                listaIndicesFotoParaMoverFotos.append( listaIndicesFoto.at( ui->listWidget->row(item) ) );
            }

        }
        if(ui->fotowidget->isVisible())
        {
            QModelIndexList selection = ui->fotowidget->selectionModel()->selectedRows();
            for(int i=0; i< selection.count(); i++)
            {
                QModelIndex index = selection.at(i);
                listaIndicesAlbumParaMoverFotos.append( listaIndicesAlbum.at(index.row()) );
                listaIndicesPaginaParaMoverFotos.append( listaIndicesPagina.at(index.row()) );
                listaIndicesFotoParaMoverFotos.append( listaIndicesFoto.at(index.row()) );
            }

        }

    }

    moverFotos = true;
}
//=========================================================================================
void MainWindow::CopiarFotosParte1()
{
    if(listaIndicesAlbum.isEmpty())
    {
        indiceAlbumParaMoverFotos = ui->albumwidget->currentIndex().parent().row();
        indicePaginaParaMoverFotos = ui->albumwidget->currentIndex().row();
        indiceFotosParaMoverFotos.clear();

        if(ui->listWidget->isVisible())
        {
            QList<QListWidgetItem*> items = ui->listWidget->selectedItems();

            foreach(QListWidgetItem * item, items)
            {
                indiceFotosParaMoverFotos.append(ui->listWidget->row(item));
            }

        }
        if(ui->fotowidget->isVisible())
        {
            //QItemSelection selection( ui->fotowidget->selectionModel()->selection() );
            QModelIndexList selection = ui->fotowidget->selectionModel()->selectedRows();
            for(int i=0; i< selection.count(); i++)
            {
                QModelIndex index = selection.at(i);
                indiceFotosParaMoverFotos.append( index.row());
            }
        }
    }

    else
    {
        listaIndicesAlbumParaMoverFotos.clear();
        listaIndicesPaginaParaMoverFotos.clear();
        listaIndicesFotoParaMoverFotos.clear();

        if(ui->listWidget->isVisible())
        {
            QList<QListWidgetItem*> items = ui->listWidget->selectedItems();

            foreach(QListWidgetItem * item, items)
            {
                listaIndicesAlbumParaMoverFotos.append( listaIndicesAlbum.at( ui->listWidget->row(item) ) );
                listaIndicesPaginaParaMoverFotos.append( listaIndicesPagina.at( ui->listWidget->row(item) ) );
                listaIndicesFotoParaMoverFotos.append( listaIndicesFoto.at( ui->listWidget->row(item) ) );
            }

        }
        if(ui->fotowidget->isVisible())
        {
            QModelIndexList selection = ui->fotowidget->selectionModel()->selectedRows();
            for(int i=0; i< selection.count(); i++)
            {
                QModelIndex index = selection.at(i);
                listaIndicesAlbumParaMoverFotos.append( listaIndicesAlbum.at(index.row()) );
                listaIndicesPaginaParaMoverFotos.append( listaIndicesPagina.at(index.row()) );
                listaIndicesFotoParaMoverFotos.append( listaIndicesFoto.at(index.row()) );
            }

        }

    }

    copiarFotos = true;
}
//=========================================================================================
void MainWindow::CopiarFotosParte2()
{
    if(listaIndicesAlbumParaMoverFotos.isEmpty())
    {
        if(!ui->albumwidget->currentItem()->parent()) // se o elemento da albumwidget seleccionado for um album
        {
            int albumDestino = ui->albumwidget->currentIndex().row();

            if(ListaAlbum.at(albumDestino)->ListaPagina.isEmpty())
            {
                NovaPagina *np = new NovaPagina(albumDestino,0);
                int dialogCode = np->exec();
                if(dialogCode == QDialog::Accepted)
                {
                    Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.first();


                    std::sort(indiceFotosParaMoverFotos.begin(),indiceFotosParaMoverFotos.end());


                    for (int s = indiceFotosParaMoverFotos.count()-1; s>=0; s-=1)
                    {
                        QFile c;
                        QString localizacao = ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto();
                        QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.first()->getPastaPagina();
                        novaLocalizacao += "/";
                        novaLocalizacao += ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at( indiceFotosParaMoverFotos.at(s))->getNomeFoto();

                        c.copy(localizacao, novaLocalizacao );

                        QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                        QString nomeF = fileInfo.fileName();

                        m_pixmap.load(novaLocalizacao);

                        QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                        QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                        ListaAlbum.at(albumDestino)->ListaPagina.first()->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));

                        for(int j=0; j<atual->ListaPessoas.count(); j++)
                        {
                            atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                        }

                        for(int g=0; g<indiceFotosParaMoverFotos.count();g++)
                        {
                            if(indiceFotosParaMoverFotos.at(g)>indiceFotosParaMoverFotos.at(s))
                            {
                                indiceFotosParaMoverFotos[g]=indiceFotosParaMoverFotos.at(g)-1;
                            }
                        }
                    }
                    MainWindow::refreshTreeWidget();

                    ui->actionNova_Pagina->setEnabled(false);
                    ui->actionEditar->setEnabled(false);
                    ui->actionAdicionar_Fotografias->setEnabled(false);
                    ui->actionAdicionar_Pasta->setEnabled(false);
                    ui->actionAssociar_Pessoas->setEnabled(false);
                }
            }
            else
            {
                if(albumDestino == indiceAlbumParaMoverFotos)
                {
                    QMessageBox::critical(this, "ERRO!", "As fotos seleccionadas já se encontram na página do álbum escolhido.");

                }
                else
                {
                    Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.first();

                    std::sort(indiceFotosParaMoverFotos.begin(),indiceFotosParaMoverFotos.end());


                    for (int s = indiceFotosParaMoverFotos.count()-1; s>=0; s-=1)
                    {
                        QFile c;
                        QString localizacao = ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto();
                        QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.first()->getPastaPagina();
                        novaLocalizacao += "/";
                        novaLocalizacao += ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at( indiceFotosParaMoverFotos.at(s))->getNomeFoto();

                        c.copy(localizacao, novaLocalizacao );

                        QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                        QString nomeF = fileInfo.fileName();

                        m_pixmap.load(novaLocalizacao);

                        QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                        QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                        ListaAlbum.at(albumDestino)->ListaPagina.first()->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));


                        for(int j=0; j<atual->ListaPessoas.count(); j++)
                        {
                            atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                        }
                        for(int g=0; g<indiceFotosParaMoverFotos.count();g++)
                        {
                            if(indiceFotosParaMoverFotos.at(g)>indiceFotosParaMoverFotos.at(s))
                            {
                                indiceFotosParaMoverFotos[g]=indiceFotosParaMoverFotos.at(g)-1;
                            }
                        }
                    }
                }
            }
        }

        else
        {
            int albumDestino = ui->albumwidget->currentIndex().parent().row();
            int paginaDestino = ui->albumwidget->currentIndex().row();

            if((albumDestino == indiceAlbumParaMoverFotos) && (indicePaginaParaMoverFotos == paginaDestino ))
            {
                QMessageBox::critical(this, "ERRO!", "As fotos seleccionadas já se encontram na página do álbum escolhido.");

            }
            else
            {
                Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.at(paginaDestino);

                std::sort(indiceFotosParaMoverFotos.begin(),indiceFotosParaMoverFotos.end());
                for (int s = indiceFotosParaMoverFotos.count()-1; s>=0; s-=1)
                {

                    QFile c;
                    QString localizacao = ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto();
                    QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.at(paginaDestino)->getPastaPagina();
                    novaLocalizacao += "/";
                    novaLocalizacao += ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at( indiceFotosParaMoverFotos.at(s))->getNomeFoto();

                    c.copy(localizacao, novaLocalizacao );

                    QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                    QString nomeF = fileInfo.fileName();

                    m_pixmap.load(novaLocalizacao);

                    QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                    QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                    ListaAlbum.at(albumDestino)->ListaPagina.at(paginaDestino)->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));
                    for(int j=0; j<atual->ListaPessoas.count(); j++)
                    {
                        atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                    }
                    for(int g=0; g<indiceFotosParaMoverFotos.count();g++)
                    {
                        if(indiceFotosParaMoverFotos.at(g)>indiceFotosParaMoverFotos.at(s))
                        {
                            indiceFotosParaMoverFotos[g]=indiceFotosParaMoverFotos.at(g)-1;
                        }
                    }


                }

            }
        }
    }
    else
    {
        if(!ui->albumwidget->currentItem()->parent()) // se o elemento da albumwidget seleccionado for um album
        {
            int albumDestino = ui->albumwidget->currentIndex().row();

            if(ListaAlbum.at(albumDestino)->ListaPagina.isEmpty())
            {
                NovaPagina *np = new NovaPagina(albumDestino,0);
                int dialogCode = np->exec();
                if(dialogCode == QDialog::Accepted)
                {
                    Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.first();
                    for (int s = listaIndicesFotoParaMoverFotos.count()-1; s>=0; s-=1)
                    {
                        if((albumDestino == listaIndicesAlbumParaMoverFotos.at(s)) && (listaIndicesPaginaParaMoverFotos.at(s) == 0 ))
                        {
                        }
                        else
                        {
                            QFile c;
                            QString localizacao = ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto();
                            QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.first()->getPastaPagina();
                            novaLocalizacao += "/";
                            novaLocalizacao += ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getNomeFoto();

                            c.copy(localizacao, novaLocalizacao );

                            QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                            QString nomeF = fileInfo.fileName();

                            m_pixmap.load(novaLocalizacao);

                            QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                            QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                            ListaAlbum.at(albumDestino)->ListaPagina.first()->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));

                            for(int j=0; j<atual->ListaPessoas.count(); j++)
                            {
                                atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                            }


                            for(int g=0; g<listaIndicesAlbumParaMoverFotos.count();g++)
                            {
                                if(listaIndicesAlbumParaMoverFotos.at(g)==listaIndicesAlbumParaMoverFotos.at(s))
                                {
                                    if(listaIndicesPaginaParaMoverFotos.at(g)==listaIndicesPaginaParaMoverFotos.at(s))
                                    {
                                        if(listaIndicesFotoParaMoverFotos.at(g)>listaIndicesFotoParaMoverFotos.at(s))
                                        {
                                            listaIndicesFotoParaMoverFotos[g]=listaIndicesFotoParaMoverFotos.at(g)-1;
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
                Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.first();


                for (int s = listaIndicesFotoParaMoverFotos.count()-1; s>=0; s-=1)
                {
                    if((albumDestino == listaIndicesAlbumParaMoverFotos.at(s)) && (listaIndicesPaginaParaMoverFotos.at(s) == 0 ))
                    {
                    }
                    else
                    {
                        QFile c;
                        QString localizacao = ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto();
                        QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.first()->getPastaPagina();
                        novaLocalizacao += "/";
                        novaLocalizacao += ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getNomeFoto();

                        c.copy(localizacao, novaLocalizacao );

                        QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                        QString nomeF = fileInfo.fileName();

                        m_pixmap.load(novaLocalizacao);

                        QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                        QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                        ListaAlbum.at(albumDestino)->ListaPagina.first()->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));

                        for(int j=0; j<atual->ListaPessoas.count(); j++)
                        {
                            atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                        }


                        for(int g=0; g<listaIndicesAlbumParaMoverFotos.count();g++)
                        {
                            if(listaIndicesAlbumParaMoverFotos.at(g)==listaIndicesAlbumParaMoverFotos.at(s))
                            {
                                if(listaIndicesPaginaParaMoverFotos.at(g)==listaIndicesPaginaParaMoverFotos.at(s))
                                {
                                    if(listaIndicesFotoParaMoverFotos.at(g)>listaIndicesFotoParaMoverFotos.at(s))
                                    {
                                        listaIndicesFotoParaMoverFotos[g]=listaIndicesFotoParaMoverFotos.at(g)-1;
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
            int albumDestino = ui->albumwidget->currentIndex().parent().row();
            int paginaDestino = ui->albumwidget->currentIndex().row();
            Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.at(paginaDestino);


            for (int s = listaIndicesFotoParaMoverFotos.count()-1; s>=0; s-=1)
            {
                if((albumDestino == listaIndicesAlbumParaMoverFotos.at(s)) && (listaIndicesPaginaParaMoverFotos.at(s) == paginaDestino ))
                {/*
               */ }
                else
                {
                    QFile c;
                    QString localizacao = ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto();
                    QString novaLocalizacao = atual->getPastaPagina();
                    novaLocalizacao += "/";
                    novaLocalizacao += ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getNomeFoto();

                    c.copy(localizacao, novaLocalizacao );

                    QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                    QString nomeF = fileInfo.fileName();

                    m_pixmap.load(novaLocalizacao);

                    QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                    QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                    atual->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));

                    for(int j=0; j<atual->ListaPessoas.count(); j++)
                    {
                        atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                    }

                    for(int g=0; g<listaIndicesAlbumParaMoverFotos.count();g++)
                    {
                        if(listaIndicesAlbumParaMoverFotos.at(g)==listaIndicesAlbumParaMoverFotos.at(s))
                        {
                            if(listaIndicesPaginaParaMoverFotos.at(g)==listaIndicesPaginaParaMoverFotos.at(s))
                            {
                                if(listaIndicesFotoParaMoverFotos.at(g)>listaIndicesFotoParaMoverFotos.at(s))
                                {
                                    listaIndicesFotoParaMoverFotos[g]=listaIndicesFotoParaMoverFotos.at(g)-1;
                                }
                            }
                        }
                    }
                }
            }
        }

    }
    if(ui->listWidget->isVisible())
    {
        ui->listWidget->clear();
    }
    if(ui->fotowidget->isVisible())
    {
        ui->fotowidget->setRowCount(0);
    }

    copiarFotos = false;

    F.escreverPaginas(ListaAlbum);
    F.escreverAssociacoes(ListaAlbum,ListaPessoa);

    listaIndicesAlbumParaMoverFotos.clear();
    listaIndicesFotoParaMoverFotos.clear();
    listaIndicesPaginaParaMoverFotos.clear();

    indiceFotosParaMoverFotos.clear();

}
//=========================================================================================
void MainWindow::MoverFotosParte2()
{
    if(listaIndicesAlbumParaMoverFotos.isEmpty())
    {
        if(!ui->albumwidget->currentItem()->parent()) // se o elemento da albumwidget seleccionado for um album
        {
            int albumDestino = ui->albumwidget->currentIndex().row();

            if(ListaAlbum.at(albumDestino)->ListaPagina.isEmpty())
            {
                NovaPagina *np = new NovaPagina(albumDestino,0);
                int dialogCode = np->exec();
                if(dialogCode == QDialog::Accepted)
                {
                    Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.first();


                    std::sort(indiceFotosParaMoverFotos.begin(),indiceFotosParaMoverFotos.end());


                    for (int s = indiceFotosParaMoverFotos.count()-1; s>=0; s-=1)
                    {
                        QFile c;
                        QString localizacao = ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto();
                        QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.first()->getPastaPagina();
                        novaLocalizacao += "/";
                        novaLocalizacao += ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at( indiceFotosParaMoverFotos.at(s))->getNomeFoto();

                        c.copy(localizacao, novaLocalizacao );

                        QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                        QString nomeF = fileInfo.fileName();

                        m_pixmap.load(novaLocalizacao);

                        QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                        QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                        ListaAlbum.at(albumDestino)->ListaPagina.first()->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));

                        for(int j=0; j<atual->ListaPessoas.count(); j++)
                        {
                            atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                        }
                        QFile (ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.first()->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto()).remove();

                        for(int g=0; g<indiceFotosParaMoverFotos.count();g++)
                        {
                            if(indiceFotosParaMoverFotos.at(g)>indiceFotosParaMoverFotos.at(s))
                            {
                                indiceFotosParaMoverFotos[g]=indiceFotosParaMoverFotos.at(g)-1;
                            }
                        }
                        ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.removeAt(indiceFotosParaMoverFotos.at(s));


                    }
                    MainWindow::refreshTreeWidget();

                    ui->actionNova_Pagina->setEnabled(false);
                    ui->actionEditar->setEnabled(false);
                    ui->actionAdicionar_Fotografias->setEnabled(false);
                    ui->actionAdicionar_Pasta->setEnabled(false);
                    ui->actionAssociar_Pessoas->setEnabled(false);
                    ui->actionSlideshow->setEnabled(false);
                }

            }

            else
            {
                if(albumDestino == indiceAlbumParaMoverFotos)
                {
                    QMessageBox::critical(this, "ERRO!", "As fotos seleccionadas já se encontram na página do álbum escolhido.");

                }
                else
                {
                    Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.first();

                    std::sort(indiceFotosParaMoverFotos.begin(),indiceFotosParaMoverFotos.end());


                    for (int s = indiceFotosParaMoverFotos.count()-1; s>=0; s-=1)
                    {
                        QFile c;
                        QString localizacao = ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto();
                        QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.first()->getPastaPagina();
                        novaLocalizacao += "/";
                        novaLocalizacao += ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at( indiceFotosParaMoverFotos.at(s))->getNomeFoto();

                        c.copy(localizacao, novaLocalizacao );

                        QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                        QString nomeF = fileInfo.fileName();

                        m_pixmap.load(novaLocalizacao);

                        QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                        QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                        ListaAlbum.at(albumDestino)->ListaPagina.first()->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));


                        for(int j=0; j<atual->ListaPessoas.count(); j++)
                        {
                            atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                        }


                        QFile (ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.first()->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto()).remove();

                        for(int g=0; g<indiceFotosParaMoverFotos.count();g++)
                        {
                            if(indiceFotosParaMoverFotos.at(g)>indiceFotosParaMoverFotos.at(s))
                            {
                                indiceFotosParaMoverFotos[g]=indiceFotosParaMoverFotos.at(g)-1;
                            }
                        }

                        ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.removeAt(indiceFotosParaMoverFotos.at(s));


                    }
                }
            }
        }

        else
        {
            int albumDestino = ui->albumwidget->currentIndex().parent().row();
            int paginaDestino = ui->albumwidget->currentIndex().row();

            if((albumDestino == indiceAlbumParaMoverFotos) && (indicePaginaParaMoverFotos == paginaDestino ))
            {
                QMessageBox::critical(this, "ERRO!", "As fotos seleccionadas já se encontram na página do álbum escolhido.");

            }
            else
            {
                Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.at(paginaDestino);

                std::sort(indiceFotosParaMoverFotos.begin(),indiceFotosParaMoverFotos.end());


                for (int s = indiceFotosParaMoverFotos.count()-1; s>=0; s-=1)
                {

                    QFile c;
                    QString localizacao = ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto();
                    QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.at(paginaDestino)->getPastaPagina();
                    novaLocalizacao += "/";
                    novaLocalizacao += ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at( indiceFotosParaMoverFotos.at(s))->getNomeFoto();

                    c.copy(localizacao, novaLocalizacao );

                    QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                    QString nomeF = fileInfo.fileName();

                    m_pixmap.load(novaLocalizacao);

                    QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                    QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                    ListaAlbum.at(albumDestino)->ListaPagina.at(paginaDestino)->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));


                    for(int j=0; j<atual->ListaPessoas.count(); j++)
                    {
                        atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                    }


                    QFile (ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.at(indiceFotosParaMoverFotos.at(s))->getDirectorioFoto()).remove();

                    for(int g=0; g<indiceFotosParaMoverFotos.count();g++)
                    {
                        if(indiceFotosParaMoverFotos.at(g)>indiceFotosParaMoverFotos.at(s))
                        {
                            indiceFotosParaMoverFotos[g]=indiceFotosParaMoverFotos.at(g)-1;
                        }
                    }
                    ListaAlbum.at(indiceAlbumParaMoverFotos)->ListaPagina.at(indicePaginaParaMoverFotos)->ListaFotos.removeAt(indiceFotosParaMoverFotos.at(s));

                }

            }
        }
    }

    else
    {
        if(!ui->albumwidget->currentItem()->parent()) // se o elemento da albumwidget seleccionado for um album
        {
            int albumDestino = ui->albumwidget->currentIndex().row();

            if(ListaAlbum.at(albumDestino)->ListaPagina.isEmpty())
            {
                NovaPagina *np = new NovaPagina(albumDestino,0);
                int dialogCode = np->exec();
                if(dialogCode == QDialog::Accepted)
                {
                    Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.first();


                    for (int s = listaIndicesFotoParaMoverFotos.count()-1; s>=0; s-=1)
                    {
                        if((albumDestino == listaIndicesAlbumParaMoverFotos.at(s)) && (listaIndicesPaginaParaMoverFotos.at(s) == 0 ))
                        {
                            listaIndicesAlbumParaMoverFotos.removeAt(s);
                            listaIndicesPaginaParaMoverFotos.removeAt(s);
                            listaIndicesFotoParaMoverFotos.removeAt(s);

                        }
                        else
                        {
                            QFile c;
                            QString localizacao = ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto();
                            QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.first()->getPastaPagina();
                            novaLocalizacao += "/";
                            novaLocalizacao += ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getNomeFoto();

                            c.copy(localizacao, novaLocalizacao );

                            QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                            QString nomeF = fileInfo.fileName();

                            m_pixmap.load(novaLocalizacao);

                            QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                            QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                            ListaAlbum.at(albumDestino)->ListaPagina.first()->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));

                            for(int j=0; j<atual->ListaPessoas.count(); j++)
                            {
                                atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                            }


                            QFile (ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto()).remove();

                            for(int g=0; g<listaIndicesAlbumParaMoverFotos.count();g++)
                            {
                                if(listaIndicesAlbumParaMoverFotos.at(g)==listaIndicesAlbumParaMoverFotos.at(s))
                                {
                                    if(listaIndicesPaginaParaMoverFotos.at(g)==listaIndicesPaginaParaMoverFotos.at(s))
                                    {
                                        if(listaIndicesFotoParaMoverFotos.at(g)>listaIndicesFotoParaMoverFotos.at(s))
                                        {
                                            listaIndicesFotoParaMoverFotos[g]=listaIndicesFotoParaMoverFotos.at(g)-1;
                                        }
                                    }
                                }
                            }
                            ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.removeAt(listaIndicesFotoParaMoverFotos.at(s));
                        }
                    }
                }

            }
            else
            {
                Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.first();


                for (int s = listaIndicesFotoParaMoverFotos.count()-1; s>=0; s-=1)
                {
                    if((albumDestino == listaIndicesAlbumParaMoverFotos.at(s)) && (listaIndicesPaginaParaMoverFotos.at(s) == 0 ))
                    {
                        listaIndicesAlbumParaMoverFotos.removeAt(s);
                        listaIndicesPaginaParaMoverFotos.removeAt(s);
                        listaIndicesFotoParaMoverFotos.removeAt(s);

                    }
                    else
                    {
                        QFile c;
                        QString localizacao = ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto();
                        QString novaLocalizacao = ListaAlbum.at(albumDestino)->ListaPagina.first()->getPastaPagina();
                        novaLocalizacao += "/";
                        novaLocalizacao += ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getNomeFoto();

                        c.copy(localizacao, novaLocalizacao );

                        QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                        QString nomeF = fileInfo.fileName();

                        m_pixmap.load(novaLocalizacao);

                        QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                        QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                        ListaAlbum.at(albumDestino)->ListaPagina.first()->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));

                        for(int j=0; j<atual->ListaPessoas.count(); j++)
                        {
                            atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                        }


                        QFile (ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto()).remove();

                        for(int g=0; g<listaIndicesAlbumParaMoverFotos.count();g++)
                        {
                            if(listaIndicesAlbumParaMoverFotos.at(g)==listaIndicesAlbumParaMoverFotos.at(s))
                            {
                                if(listaIndicesPaginaParaMoverFotos.at(g)==listaIndicesPaginaParaMoverFotos.at(s))
                                {
                                    if(listaIndicesFotoParaMoverFotos.at(g)>listaIndicesFotoParaMoverFotos.at(s))
                                    {
                                        listaIndicesFotoParaMoverFotos[g]=listaIndicesFotoParaMoverFotos.at(g)-1;
                                    }
                                }
                            }
                        }
                        ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.removeAt(listaIndicesFotoParaMoverFotos.at(s));
                    }
                }
            }

        }

        else
        {
            int albumDestino = ui->albumwidget->currentIndex().parent().row();
            int paginaDestino = ui->albumwidget->currentIndex().row();
            Pagina *atual = ListaAlbum.at(albumDestino)->ListaPagina.at(paginaDestino);


            for (int s = listaIndicesFotoParaMoverFotos.count()-1; s>=0; s-=1)
            {
                if((albumDestino == listaIndicesAlbumParaMoverFotos.at(s)) && (listaIndicesPaginaParaMoverFotos.at(s) == paginaDestino ))
                {
                    listaIndicesAlbumParaMoverFotos.removeAt(s);
                    listaIndicesPaginaParaMoverFotos.removeAt(s);
                    listaIndicesFotoParaMoverFotos.removeAt(s);

                }
                else
                {
                    QFile c;
                    QString localizacao = ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto();
                    QString novaLocalizacao = atual->getPastaPagina();
                    novaLocalizacao += "/";
                    novaLocalizacao += ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getNomeFoto();

                    c.copy(localizacao, novaLocalizacao );

                    QFileInfo fileInfo(novaLocalizacao);// Meter como atributo da lista Foto
                    QString nomeF = fileInfo.fileName();

                    m_pixmap.load(novaLocalizacao);

                    QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                    QString data = fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate);

                    atual->ListaFotos.append(new Foto(nomeF,novaLocalizacao,resolucao,data,fileInfo));

                    for(int j=0; j<atual->ListaPessoas.count(); j++)
                    {
                        atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                    }


                    QFile (ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.at(listaIndicesFotoParaMoverFotos.at(s))->getDirectorioFoto()).remove();

                    for(int g=0; g<listaIndicesAlbumParaMoverFotos.count();g++)
                    {
                        if(listaIndicesAlbumParaMoverFotos.at(g)==listaIndicesAlbumParaMoverFotos.at(s))
                        {
                            if(listaIndicesPaginaParaMoverFotos.at(g)==listaIndicesPaginaParaMoverFotos.at(s))
                            {
                                if(listaIndicesFotoParaMoverFotos.at(g)>listaIndicesFotoParaMoverFotos.at(s))
                                {
                                    listaIndicesFotoParaMoverFotos[g]=listaIndicesFotoParaMoverFotos.at(g)-1;
                                }
                            }
                        }
                    }
                    ListaAlbum.at(listaIndicesAlbumParaMoverFotos.at(s))->ListaPagina.at(listaIndicesPaginaParaMoverFotos.at(s))->ListaFotos.removeAt(listaIndicesFotoParaMoverFotos.at(s));

                }
            }
        }

    }

    if(ui->listWidget->isVisible())
    {
        ui->listWidget->clear();
    }
    if(ui->fotowidget->isVisible())
    {
        ui->fotowidget->setRowCount(0);
    }

    moverFotos = false;

    F.escreverPaginas(ListaAlbum);
    F.escreverAssociacoes(ListaAlbum,ListaPessoa);

    listaIndicesAlbumParaMoverFotos.clear();
    listaIndicesFotoParaMoverFotos.clear();
    listaIndicesPaginaParaMoverFotos.clear();

    indiceFotosParaMoverFotos.clear();

}
//=========================================================================================
void MainWindow::calcularDatas()
{
    QDate DinicioA, DfimA, DinicioP, DfimP;
    if(!ui->albumwidget->currentItem()->parent())//Album selecionado
    {
        Album *atualA = ListaAlbum.at(ui->albumwidget->currentIndex().row());
        for(int i = 0; i<atualA->ListaPagina.count();i++)
        {
            if(i == 0)
            {
                DinicioA = atualA->ListaPagina.at(i)->getDataInicioPagina();
                DfimA = atualA->ListaPagina.at(i)->getDataFimPagina();
            }
            else
            {
                if(DinicioA > atualA->ListaPagina.at(i)->getDataInicioPagina())
                    DinicioA = atualA->ListaPagina.at(i)->getDataInicioPagina();
                if(DfimA < atualA->ListaPagina.at(i)->getDataFimPagina())
                    DfimA = atualA->ListaPagina.at(i)->getDataFimPagina();
            }
        }

        atualA->setDataInicioAlbum(DinicioA);
        atualA->setDataFimAlbum(DfimA);
    }


    else//Pagina selecionada
    {

        int indexA = ui->albumwidget->currentIndex().parent().row();
        int indexP = ui->albumwidget->currentIndex().row();
        Pagina *atual = ListaAlbum.at(indexA)->ListaPagina.at(indexP);

        if(atual->getTipoDePagina() != "Outro" && atual->getTipoDePagina() != "Viagem"){
            QString Final, Inicial;
            int str;
            for(int k=0; k<atual->ListaFotos.count() ; k++)
            {
                str = atual->ListaFotos.at(0)->getDataFoto().lastIndexOf(QChar(' '));

                if(k == 0)
                {
                    Final = atual->ListaFotos.at(0)->getDataFoto().left(str); Inicial = atual->ListaFotos.at(0)->getDataFoto().left(str);
                }
                else
                {
                    Final = MainWindow::compararstrdatasFinal(Final,atual->ListaFotos.at(k)->getDataFoto().left(str));
                    Inicial = MainWindow::compararstrdatasInicial(Inicial,atual->ListaFotos.at(k)->getDataFoto().left(str));
                }
            }

            DfimP = QDate::fromString(Final,"dd-MM-yyyy");
            DinicioP = QDate::fromString(Inicial,"dd-MM-yyyy");
            atual->setDataFinal(DfimP);
            atual->setDataInicial(DinicioP);

        }
    }

}
//=========================================================================================

QString MainWindow::compararstrdatasInicial(QString str1, QString str2)
{
    QRegExp separator("-");
    int ano1,ano2,mes1,mes2,dia1,dia2;
    QStringList list1 = str1.split(separator);
    QStringList list2 = str2.split(separator);
    ano1 = list1.at(2).toInt();
    ano2 = list2.at(2).toInt();
    mes1 = list1.at(1).toInt();
    mes2 = list2.at(1).toInt();
    dia1 = list1.at(0).toInt();
    dia2 = list2.at(0).toInt();

    if(ano1 < ano2)
        return(str1);
    else if(ano2 < ano1)
        return(str2);
    else{
        if(mes1 < mes2)
            return(str1);
        else if(mes2 < mes1)
            return(str2);
        else{
            if(dia1 < dia2)
                return(str1);
            else
                return(str2);
        }
    }
}

//=========================================================================================

QString MainWindow::compararstrdatasFinal(QString str1, QString str2)
{
    QRegExp separator("-");
    int ano1,ano2,mes1,mes2,dia1,dia2;
    QStringList list1 = str1.split(separator);
    QStringList list2 = str2.split(separator);
    ano1 = list1.at(2).toInt();
    ano2 = list2.at(2).toInt();
    mes1 = list1.at(1).toInt();
    mes2 = list2.at(1).toInt();
    dia1 = list1.at(0).toInt();
    dia2 = list2.at(0).toInt();

    if(ano1 > ano2)
        return(str1);
    else if(ano2 > ano1)
        return(str2);
    else{
        if(mes1 > mes2)
            return(str1);
        else if(mes2 > mes1)
            return(str2);
        else{
            if(dia1 > dia2)
                return(str1);
            else
                return(str2);
        }
    }
}
//=========================================================================================
