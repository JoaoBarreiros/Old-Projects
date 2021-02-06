#include "configuracaoniveis.h"
#include "ui_configuracaoniveis.h"

ConfiguracaoNiveis::ConfiguracaoNiveis(int i,QString dir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfiguracaoNiveis)
{
    ui->setupUi(this);

    directorio = dir;
    index = i;
}
//=========================================================================================
ConfiguracaoNiveis::~ConfiguracaoNiveis()
{
    //m_pixmap.~QPixmap();
    delete ui;
}
//=========================================================================================
void ConfiguracaoNiveis::on_OK_clicked()
{
    int numeroNiveis = ui->spinBox->value();


    QList <QString> mapaCaminhos;
    QList <int> indicesPaginas;

    int iteracao = 0;
    int separadorPastaInicial;
    int separador;



    QDirIterator it(directorio, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QFileInfo informacao(it.next());
        QString caminhoDoFicheiro = informacao.absoluteFilePath();
        QString nomeDoFicheiro = informacao.fileName();
        QString caminho = informacao.path();


        if(iteracao == 0)
        {
            iteracao++;
            separadorPastaInicial = caminhoDoFicheiro.count(QChar('/'), Qt::CaseSensitive);
        }

        separador = caminhoDoFicheiro.count(QChar('/'), Qt::CaseSensitive);




        if(separador > separadorPastaInicial && separador <= (numeroNiveis+separadorPastaInicial))
        {
            if(separador == separadorPastaInicial+1)
            {
                if(!informacao.isDir())
                {
                    if( nomeDoFicheiro.contains(".png",Qt::CaseSensitive) || nomeDoFicheiro.contains(".jpg",Qt::CaseSensitive) || nomeDoFicheiro.contains(".tiff",Qt::CaseSensitive) || nomeDoFicheiro.contains(".svg",Qt::CaseSensitive) || nomeDoFicheiro.contains(".raw",Qt::CaseSensitive))
                    {

                        if(ListaAlbum.at(index)->ListaPagina.isEmpty())
                        {
                            NovaPagina *np = new NovaPagina(index,0);
                            int dialogCode = np->exec();
                            if(dialogCode == QDialog::Accepted)
                            {
                                Pagina *atual = ListaAlbum.at(index)->ListaPagina.last();

                                //QPixmap pix(caminhoDoFicheiro);//Meter como atributo da lista Foto
                                m_pixmap.load(caminhoDoFicheiro);

                                QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                                QString data = informacao.birthTime().toString(Qt::DefaultLocaleShortDate);

                                QFile a;
                                QString novaLocalizacao = atual->getPastaPagina();
                                novaLocalizacao+="/";
                                novaLocalizacao+=nomeDoFicheiro;
                                a.copy(caminhoDoFicheiro,novaLocalizacao);

                                atual->ListaFotos.append(new Foto(nomeDoFicheiro,novaLocalizacao,resolucao,data,informacao));

                                for(int j=0; j<atual->ListaPessoas.count(); j++)
                                {
                                    atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                                }

                                //F.escreverFotos(ListaAlbum,index,0);

                            }
                        }
                        else
                        {
                            Pagina *atual = ListaAlbum.at(index)->ListaPagina.first();

                            //QPixmap pix(caminhoDoFicheiro);//Meter como atributo da lista Foto
                            m_pixmap.load(caminhoDoFicheiro);
                            QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                            QString data = informacao.birthTime().toString(Qt::DefaultLocaleShortDate);

                            QFile a;
                            QString novaLocalizacao = atual->getPastaPagina();
                            novaLocalizacao+="/";
                            novaLocalizacao+=nomeDoFicheiro;
                            a.copy(caminhoDoFicheiro,novaLocalizacao);

                            atual->ListaFotos.append(new Foto(nomeDoFicheiro,novaLocalizacao,resolucao,data,informacao));

                            for(int j=0; j<atual->ListaPessoas.count(); j++)
                            {
                                atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                            }

                        }
                    }
                }
            }
            else
            {
                if(!informacao.isDir())
                {
                    if( nomeDoFicheiro.contains(".png",Qt::CaseSensitive) || nomeDoFicheiro.contains(".jpg",Qt::CaseSensitive) || nomeDoFicheiro.contains(".tiff",Qt::CaseSensitive) || nomeDoFicheiro.contains(".svg",Qt::CaseSensitive) || nomeDoFicheiro.contains(".raw",Qt::CaseSensitive))
                    {
                        int indiceCaminho = mapaCaminhos.indexOf(caminho);


                        if(indiceCaminho==-1)
                        {
                            NovaPagina *np = new NovaPagina(index,0);
                            int dialogCode = np->exec();
                            if(dialogCode == QDialog::Accepted)
                            {
                                Pagina *atual = ListaAlbum.at(index)->ListaPagina.last();

                                //QPixmap pix(caminhoDoFicheiro);//Meter como atributo da lista Foto
                                m_pixmap.load(caminhoDoFicheiro);
                                QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                                QString data = informacao.birthTime().toString(Qt::DefaultLocaleShortDate);

                                QFile a;
                                QString novaLocalizacao = atual->getPastaPagina();
                                novaLocalizacao+="/";
                                novaLocalizacao+=nomeDoFicheiro;
                                a.copy(caminhoDoFicheiro,novaLocalizacao);

                                atual->ListaFotos.append(new Foto(nomeDoFicheiro,novaLocalizacao,resolucao,data,informacao));

                                for(int j=0; j<atual->ListaPessoas.count(); j++)
                                {
                                    atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                                }

                                //F.escreverFotos(ListaAlbum,index,0);
                                mapaCaminhos.append(caminho);
                                indicesPaginas.append(ListaAlbum.at(index)->ListaPagina.count()-1);
                            }
                        }
                        else
                        {
                            Pagina *atual = ListaAlbum.at(index)->ListaPagina.at(indicesPaginas.at(mapaCaminhos.indexOf(caminho)));

                            //QPixmap pix(caminhoDoFicheiro);//Meter como atributo da lista Foto
                            m_pixmap.load(caminhoDoFicheiro);

                            QString resolucao = QString::number(m_pixmap.width())+QString("x")+QString::number(m_pixmap.height());
                            QString data = informacao.birthTime().toString(Qt::DefaultLocaleShortDate);

                            QFile a;
                            QString novaLocalizacao = atual->getPastaPagina();
                            novaLocalizacao+="/";
                            novaLocalizacao+=nomeDoFicheiro;
                            a.copy(caminhoDoFicheiro,novaLocalizacao);

                            atual->ListaFotos.append(new Foto(nomeDoFicheiro,novaLocalizacao,resolucao,data,informacao));

                            for(int j=0; j<atual->ListaPessoas.count(); j++)
                            {
                                atual->ListaFotos.last()->ListaPessoas.append(atual->ListaPessoas.at(j));
                            }

                        }
                    }
                }

            }

        }
    }
    this->close();
}
//=========================================================================================
void ConfiguracaoNiveis::on_Cancelar_clicked()
{
    this->close();
}
