/*!
 * \file album.cpp Definitions of the methods of the class Album
 */
#include "album.h"


/*!
 * \brief Album::Album is one of the Album class constructor.
 * \param nome is the Album's name.
 * \param pasta is the name of the folder that contains the album.
 * \param tipo is the type of page.
 * \param descricao is the description of the album.
 */
Album::Album(QString nome,QString pasta,QString tipo,QString descricao)
{
    nomeAlbum = nome;
    pastaAlbum = pasta;
    tipoPagina = tipo;
    descricaoAlbum = descricao;
}

/*!
 * \brief Album::Album is one of the Album class constructor.
 * \param nome is the Album's name.
 * \param pasta is the name of the folder that contains the album.
 * \param tipo is the type of page.
 * \param descricao is the description of the album.
 * \param dataInicio is the starting date of the album
 * \param dataFim is the ending date of the album
 */
Album::Album(QString nome,QString pasta,QString tipo,QString descricao, QDate dataInicio, QDate dataFim)
{
    nomeAlbum = nome;
    pastaAlbum = pasta;
    tipoPagina = tipo;
    descricaoAlbum = descricao;
    dataInicioAlbum = dataInicio;
    dataFimAlbum = dataFim;
}

/*Não usado
void Album::adicionarPagina()
{

}
//=========================================================================================
void Album::removerPagina()
{

}
*/
//=========================================================================================
void Album::setDataInicioAlbum(QDate dataInicial)
{
    this->dataInicioAlbum=dataInicial;
}
//=========================================================================================
void Album::setDataFimAlbum(QDate dataFinal)
{
    this->dataFimAlbum=dataFinal;
}
//=========================================================================================


/*!
 * \brief Album::getNome returns the album's name
 */
QString Album::getNome()
{
    return nomeAlbum;
}
//=========================================================================================
/*!
 * \brief Album::getPasta returns the page's directory
 */
QString Album::getPasta()
{
    return pastaAlbum;
}
//=========================================================================================
/*!
 * \brief Album::getDescricao returns the album's description
 */
QString Album::getDescricao()
{
    return descricaoAlbum;
}
//=========================================================================================
/*!
 * \brief Album::getTipo returns the type of page given to the album
 */
QString Album::getTipo()
{
    return tipoPagina;
}
//=========================================================================================
/*!
 * \brief Album::getDataInicioAlbum returns the starting date of the album
 */
QDate Album::getDataInicioAlbum()
{
    return dataInicioAlbum;
}
//=========================================================================================
/*!
 * \brief Album::getDataFimAlbum returns the ending date of the album
 */
QDate Album::getDataFimAlbum()
{
    return dataFimAlbum;
}
//=========================================================================================
/*!
 * \brief Album::setNome sets a new name for the album
 * \param novoNome is the name to be given to the album
 */
void Album::setNome(QString novoNome)
{
    this->nomeAlbum=novoNome;
}
//=========================================================================================
/*!
 * \brief Album::setPasta sets the album's folder name
 * \param novoNome is the name to be given to the folder
 */
void Album::setPasta(QString novoNome)
{
    this->pastaAlbum=novoNome;
}
//=========================================================================================
/*!
 * \brief Album::setDescricao sets the description of the album
 * \param novoNome is the description to be given to the album
 */
void Album::setDescricao(QString novoNome)
{
    this->descricaoAlbum=novoNome;
}
