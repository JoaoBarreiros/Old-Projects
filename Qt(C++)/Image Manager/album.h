/*!
 * \file album.h Definitions of the class Album
 */

#ifndef ALBUM_H
#include <QString>
#include <QDate>
#include "pagina.h"
#include "pessoa.h"
#define ALBUM_H

/*!
 * \brief The Album class is used to represent albums
 */
class Album
{
private:
    /*!
     * \brief nomeAlbum is the name of the album
     */
    QString nomeAlbum;
    /*!
     * \brief pastaAlbum is the name of the folder that contains the album
     */
    QString pastaAlbum;
    /*!
     * \brief descricaoAlbum is the description of the album
     */
    QString descricaoAlbum;
    /*!
     * \brief tipoPagina is the type of page
     */
    QString tipoPagina;
    /*!
     * \brief dataInicioAlbum is the starting date of the album
     */
    QDate dataInicioAlbum;
    /*!
     * \brief dataFimAlbum is the ending date of the album
     */
    QDate dataFimAlbum;


public:
    Album(QString,QString,QString,QString);
    Album(QString,QString,QString,QString,QDate,QDate);
    QList <Pagina*> ListaPagina;
    QList <Pessoa*> ListaPessoas;
    /*
    void adicionarPagina();
    void removerPagina();
    QDate calcularDataInicioAlbum();
    QDate calcularDataFimAlbum();
    */
    QString getNome();
    QString getPasta();
    QString getDescricao();
    QString getTipo();
    QDate getDataInicioAlbum();
    QDate getDataFimAlbum();
    void setNome(QString);
    void setPasta(QString);
    void setDescricao(QString);
    void setDataInicioAlbum(QDate);
    void setDataFimAlbum(QDate);

};

#endif // ALBUM_H
