/*!
 * \file ficheiros.h Definitions of the class Ficheiros
 */
//=============================================================================
#ifndef FICHEIROS_H
#define FICHEIROS_H
//=============================================================================
#include <QApplication>
#include <QObject>
#include <QString>
#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QPixmap>
#include <QDir>
#include "album.h"
#include "pagina.h"
#include "pessoa.h"


extern QList <Album*> ListaAlbum;
/*!
 * \brief The Ficheiros class is used for saving this program's data permanently using binary files.
 */
//=============================================================================
class Ficheiros{

private:
    /*!
     * \brief DirectorioListaPessoas gives us the directory of the file used to save all Pessoas's information.
     */
    QString DirectorioListaPessoas;
    /*!
     * \brief DirectorioListaAlbuns gives us the directory of the file used to save all Albuns's information.
     */
    QString DirectorioListaAlbuns;
    /*!
     * \brief DirectorioListaPaginas gives us the directory of the file used to save all Paginas's information.
     */
    QString DirectorioListaPaginas;
    /*!
     * \brief DirectorioListaPaginas gives us the directory of the file used to save all Fotos's information.
     */
    QString DirectorioListaFotos;

    QString DirectorioListaAssociacoes;

    /*!
     * \brief FicheiroPessoas provides an interface for reading and writing to the Pessoas's binary file.
     */
    QFile FicheiroPessoas;
    /*!
     * \brief FicheiroAlbuns provides an interface for reading and writing to the Albuns's binary file.
     */
    QFile FicheiroAlbuns;
    /*!
     * \brief FicheiroPaginas provides an interface for reading and writing to the Paginas's binary file.
     */
    QFile FicheiroPaginas;
    /*!
     * \brief FicheiroFotos provides an interface for reading and writing to the Fotos's binary file.
     */
    QFile FicheiroFotos;
    /*!
     * \brief FicheiroAssociacoes provides an interface for reading and writing to the Associacao's binary file.
     */
    QFile FicheiroAssociacoes;

public:
    Ficheiros();
    void inicializar(QList <Album*>&,QList <Pessoa*>&);
    void escreverPessoas(QList <Pessoa*>&);
    void escreverAlbuns(QList <Album*>&);
    void escreverPaginas(QList <Album*>&);
    void escreverFotos(QList <Album*>&,int,int);
    void escreverAssociacoes(QList <Album*>&,QList <Pessoa*>&);
    void inicializarAssociacoes(QList <Album*>&, QList <Pessoa*>&);

};
//=============================================================================
#endif // FICHEIROS_H

