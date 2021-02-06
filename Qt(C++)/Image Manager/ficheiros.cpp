/*!
 * \file ficheiros.cpp Definitions of the methods of the class Ficheiros
 */
//=============================================================================
#include "ficheiros.h"

//=============================================================================
/*!
 * \brief Ficheiros::Ficheiros is the constructor by default
 */
//=============================================================================
Ficheiros::Ficheiros()
{
    this->DirectorioListaPessoas     = "pessoas.txt";
    this->DirectorioListaAlbuns      = "albuns.txt";
    this->DirectorioListaPaginas     = "paginas.txt";
    this->DirectorioListaFotos       = "fotos.txt";
    this->DirectorioListaAssociacoes = "associacoes.txt";

    this->FicheiroPessoas.setFileName(this->DirectorioListaPessoas);
    this->FicheiroAlbuns.setFileName(this->DirectorioListaAlbuns);
    this->FicheiroPaginas.setFileName(this->DirectorioListaPaginas);
    this->FicheiroFotos.setFileName(this->DirectorioListaFotos);
    this->FicheiroAssociacoes.setFileName(this->DirectorioListaAssociacoes);
/*
    this->FicheiroAlbuns.resize(0);
    this->FicheiroPaginas.resize(0);
    this->FicheiroFotos.resize(0);
    this->FicheiroPessoas.resize(0);
*/

}
//=============================================================================
/*!
 * \brief Ficheiros::inicializar reads all initial data from files
 */
void Ficheiros::inicializar(QList <Album*>& ListaAlbum, QList <Pessoa*>& ListaPessoa)
{
    QString nomePessoa;
    QDate dataNascimento;
    QString genero;
    QString relacao;

    QString nomeAlbum;
    QString pastaAlbum;
    QString descricaoAlbum;
    QString tipoPagina;
    QDate dataInicioAlbum;
    QDate dataFimAlbum;

    QString nomePagina;
    QString pastaPagina;
    QString tipoDePagina;
    QString tipoDeFesta;
    QString descricaoPagina;
    QDate dataInicioPagina;
    QDate dataFimPagina;
    QDate dataPagina;

    QString directorioFoto;
    QString nomeFoto;
    QString resolucaoFoto;
    QString dataFoto;

    int indexAlbum;
    int indexPagina;
    int indexFoto;



    if(!this->FicheiroPessoas.open(QIODevice::ReadOnly))
    {
        qDebug() << "erro a abrir o ficheiro das pessoas: " << this->FicheiroPessoas.error();
        //return;
    }

    else
    {
        QDataStream inP(&this->FicheiroPessoas);
        inP.setVersion(QDataStream::Qt_5_10);

        while(!inP.atEnd())
        {
           inP >> nomePessoa >> dataNascimento >> genero >> relacao;
           ListaPessoa.append(new Pessoa(nomePessoa,dataNascimento,genero,relacao));

        }

        this->FicheiroPessoas.close();
    }

    if(!this->FicheiroAlbuns.open(QIODevice::ReadOnly))
    {
        qDebug() << "erro a abrir o ficheiro dos albuns: " << this->FicheiroAlbuns.error();
        //return;
    }

    else
    {
        QDataStream inA(&this->FicheiroAlbuns);
        inA.setVersion(QDataStream::Qt_5_10);

        while(!inA.atEnd())
        {
           inA >> nomeAlbum >> pastaAlbum >> descricaoAlbum >> tipoPagina >> dataInicioAlbum >> dataFimAlbum;
           if(QDir(pastaAlbum).exists())
               ListaAlbum.append(new Album(nomeAlbum,pastaAlbum,tipoPagina,descricaoAlbum,dataInicioAlbum,dataFimAlbum));
           else
           {
                //remover do ficheiro
           }

        }

        this->FicheiroAlbuns.close();

        if(!this->FicheiroPaginas.open(QIODevice::ReadOnly))
        {
            qDebug() << "erro a abrir o ficheiro das paginas: " << this->FicheiroPaginas.error();
            //return;
        }

        else
        {
            QDataStream inPa(&this->FicheiroPaginas);
            inPa.setVersion(QDataStream::Qt_5_10);

            while(!inPa.atEnd())
            {
               inPa >> indexAlbum >> nomePagina >> pastaPagina >> tipoDePagina >> tipoDeFesta >> descricaoPagina >> dataInicioPagina >> dataFimPagina >> dataPagina;
               if(QDir(pastaPagina).exists())
                   ListaAlbum.at(indexAlbum)->ListaPagina.append(new Pagina(nomePagina,pastaPagina,tipoDePagina,tipoDeFesta,descricaoPagina,dataInicioPagina,dataFimPagina,dataPagina));

               else
               {
                    //remover do ficheiro
               }
//                qDebug() << indexAlbum << nomePagina;
            }

            this->FicheiroPaginas.close();
/*/
            if(!this->FicheiroFotos.open(QIODevice::ReadOnly))
            {
                qDebug() << "erro a abrir o ficheiro das fotos: " << this->FicheiroFotos.error();
                //return;
            }

            else
            {
                QDataStream in(&this->FicheiroFotos);
                in.setVersion(QDataStream::Qt_5_10);

                while(!in.atEnd())
                {
                   in >> indexAlbum >> indexPagina >> directorioFoto >> nomeFoto >> resolucaoFoto >> dataFoto;
                   qDebug() << indexAlbum << indexPagina << directorioFoto << nomeFoto << resolucaoFoto << dataFoto;
                   //Pagina *atual = ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina);
                   //atual->ListaFotos.append(new Foto(nomeFoto,directorioFoto,resolucaoFoto,dataFoto));

                }

                this->FicheiroFotos.close();

            }*/

        }
    }
}
//=============================================================================
/*!
 * \brief Ficheiros::escreverPessoas saves information about a list of people
 */
void Ficheiros::escreverPessoas(QList <Pessoa*>& ListaPessoa)
{

    if(!this->FicheiroPessoas.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug() << "erro a abrir o ficheiro das pessoas: " << this->FicheiroPessoas.error();
        //return;
    }
    else
    {
        QDataStream out(&this->FicheiroPessoas);
        out.setVersion(QDataStream::Qt_5_10);

        for(int i=0; i<ListaPessoa.count(); i++)
        {
           out << ListaPessoa.at(i)->getNomePessoa() << ListaPessoa.at(i)->getDataNascimento() << ListaPessoa.at(i)->getGenero() << ListaPessoa.at(i)->getRelacao();
        }

        this->FicheiroPessoas.close();
    }
}

//=============================================================================
/*!
 * \brief Ficheiros::escreverAlbuns saves information about the list of albums
 */
void Ficheiros::escreverAlbuns(QList <Album*>& ListaAlbum)
{

    if(!this->FicheiroAlbuns.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug() << "erro a abrir o ficheiro dos albuns: " << this->FicheiroAlbuns.error();
        //return;
    }
    else
    {
        QDataStream out(&this->FicheiroAlbuns);
        out.setVersion(QDataStream::Qt_5_10);
/*
        out << ListaAlbum.last()->getNome() << ListaAlbum.last()->getPasta() << ListaAlbum.last()->getDescricao() << ListaAlbum.last()->getTipo() << ListaAlbum.last()->getDataInicioAlbum() << ListaAlbum.last()->getDataFimAlbum();
*/
        for(int i=0; i<ListaAlbum.count(); i++)
        {

           out << ListaAlbum.at(i)->getNome() << ListaAlbum.at(i)->getPasta() << ListaAlbum.at(i)->getDescricao() << ListaAlbum.at(i)->getTipo() << ListaAlbum.at(i)->getDataInicioAlbum() << ListaAlbum.at(i)->getDataFimAlbum();
        }

        this->FicheiroAlbuns.close();
    }
}
//=============================================================================
/*!
 * \brief Ficheiros::escreverPaginas saves information about a list of pages.
 */
void Ficheiros::escreverPaginas(QList <Album*>& ListaAlbum)
{

    if(!this->FicheiroPaginas.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug() << "erro a abrir o ficheiro das paginas: " << this->FicheiroPaginas.error();
        //return;
    }
    else
    {
        QDataStream out(&this->FicheiroPaginas);
        out.setVersion(QDataStream::Qt_5_10);
/*
        out << j << ListaAlbum.at(j)->ListaPagina.last()->getNomePagina() << ListaAlbum.at(j)->ListaPagina.last()->getPastaPagina() << ListaAlbum.at(j)->ListaPagina.last()->getTipoDePagina() << ListaAlbum.at(j)->ListaPagina.last()->getTipoDeFesta() << ListaAlbum.at(j)->ListaPagina.last()->getDescricaoPagina() << ListaAlbum.at(j)->ListaPagina.last()->getDataInicioPagina() << ListaAlbum.at(j)->ListaPagina.last()->getDataFimPagina() << ListaAlbum.at(j)->ListaPagina.last()->getDataPagina();
                qDebug() << j <<ListaAlbum.at(j)->ListaPagina.last()->getNomePagina();
*/
        for(int i=0; i<ListaAlbum.count(); i++)
        {
            for(int j=0; j<ListaAlbum.at(i)->ListaPagina.count(); j++)
            {
                out << i << ListaAlbum.at(i)->ListaPagina.at(j)->getNomePagina() << ListaAlbum.at(i)->ListaPagina.at(j)->getPastaPagina() << ListaAlbum.at(i)->ListaPagina.at(j)->getTipoDePagina() << ListaAlbum.at(i)->ListaPagina.at(j)->getTipoDeFesta() << ListaAlbum.at(i)->ListaPagina.at(j)->getDescricaoPagina() << ListaAlbum.at(i)->ListaPagina.at(j)->getDataInicioPagina() << ListaAlbum.at(i)->ListaPagina.at(j)->getDataFimPagina() << ListaAlbum.at(i)->ListaPagina.at(j)->getDataPagina();
            }

        }

        this->FicheiroPaginas.close();
    }
}
//=============================================================================
/*!
 * \brief Ficheiros::escreverAssociacoes saves a list of people that are associated to one or more photographs
 */
void Ficheiros::escreverAssociacoes(QList <Album*>& ListaAlbum, QList <Pessoa*>& ListaPessoas)
{
    if(!this->FicheiroAssociacoes.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug() << "erro a abrir o ficheiro das associacoes: " << this->FicheiroAssociacoes.error();
        //return;
    }
    else
    {
        QDataStream out(&this->FicheiroAssociacoes);
        out.setVersion(QDataStream::Qt_5_10);

        for(int indexAlbum=0; indexAlbum<ListaAlbum.count(); indexAlbum++)
        {
            int indexPagina = -1;
            int indexFoto = -1;

            for(int i=0; i<ListaAlbum.at(indexAlbum)->ListaPessoas.count(); i++)
            {
                out << indexAlbum << indexPagina << indexFoto << ListaAlbum.at(indexAlbum)->ListaPessoas.at(i)->getNomePessoa();
            }

            for(indexPagina=0; indexPagina<ListaAlbum.at(indexAlbum)->ListaPagina.count(); indexPagina++)
            {
                indexFoto = -1;

                for(int j=0; j<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.count(); j++)
                {
                    out << indexAlbum << indexPagina << indexFoto << ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.at(j)->getNomePessoa();
                }

                for(indexFoto=0; indexFoto<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.count(); indexFoto++)
                {
                    for(int k=0; k<ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto)->ListaPessoas.count(); k++)
                    {
                        out << indexAlbum << indexPagina << indexFoto << ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto)->ListaPessoas.at(k)->getNomePessoa();
                    }
                }
            }
        }

        this->FicheiroAssociacoes.close();
    }

}
//=============================================================================
/*!
 * \brief Ficheiros::escreverPaginas saves information about a list of photographs.
 */
void Ficheiros::escreverFotos(QList <Album*>& ListaAlbum, int i, int j)
{

    if(!this->FicheiroFotos.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug() << "erro a abrir o ficheiro das fotos: " << this->FicheiroFotos.error();
        //return;
    }
    else
    {
        QDataStream out(&this->FicheiroFotos);
        out.setVersion(QDataStream::Qt_5_10);

        out << i << j << ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.last()->getDirectorioFoto() << ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.last()->getNomeFoto() << ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.last()->getResolucaoFoto() << ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.last()->getDataFoto();

/*
        for(int i=0; i<ListaAlbum.count(); i++)
        {
            for(int j=0; j<ListaAlbum.at(i)->ListaPagina.count(); j++)
            {
                for(int k=0; k<ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.count(); k++)
                {
                    out << i << j << ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getDirectorioFoto() << ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getNomeFoto() << ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getResolucaoFoto() << ListaAlbum.at(i)->ListaPagina.at(j)->ListaFotos.at(k)->getDataFoto();
                }
            }

        }
*/
        this->FicheiroFotos.close();
    }
}
//=============================================================================
/*!
 * \brief Ficheiros::inicializarAssociacoes reads a list of people that are associated to one or more photographs
 */
void Ficheiros::inicializarAssociacoes(QList <Album*>& ListaAlbum, QList <Pessoa*>& ListaPessoa)
{
    int indexAlbum;
    int indexPagina;
    int indexFoto;
    QString nomePessoa;

    if(!this->FicheiroAssociacoes.open(QIODevice::ReadOnly))
    {
        qDebug() << "erro a abrir o ficheiro das associacoes: " << this->FicheiroAssociacoes.error();
        //return;
    }
    else
    {
        QDataStream in(&this->FicheiroAssociacoes);
        in.setVersion(QDataStream::Qt_5_10);

        while(!in.atEnd())
        {
            in >> indexAlbum >> indexPagina >> indexFoto >> nomePessoa;

            if(indexPagina==-1)
            {
                for(int i=0; i<ListaPessoa.count(); i++)
                {
                    if(nomePessoa == ListaPessoa.at(i)->getNomePessoa())
                    {
                        ListaAlbum.at(indexAlbum)->ListaPessoas.append(ListaPessoa.at(i));
                    }
                }
            }
            else
            {
                if(indexFoto==-1)
                {
                    for(int i=0; i<ListaPessoa.count(); i++)
                    {
                        if(nomePessoa == ListaPessoa.at(i)->getNomePessoa())
                        {
                            ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaPessoas.append(ListaPessoa.at(i));
                        }
                    }
                }
                else
                {
                    for(int i=0; i<ListaPessoa.count(); i++)
                    {
                        if(nomePessoa == ListaPessoa.at(i)->getNomePessoa())
                        {
                            ListaAlbum.at(indexAlbum)->ListaPagina.at(indexPagina)->ListaFotos.at(indexFoto)->ListaPessoas.append(ListaPessoa.at(i));
                        }
                    }
                }
            }
        }
        this->FicheiroAssociacoes.close();
    }
}

