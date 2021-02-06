/*!
 * \file pagina.cpp Definitions of the methods of the class Pagina
 */
#include "pagina.h"

/*!
 * \brief Pagina::Pagina is one of the Foto class constructor.
 * \param nome is the Page's name.
 * \param pasta is the Page's directory.
 * \param descricao is the page's description
 * \param tipo is the type of the page
 */
Pagina::Pagina(QString nome,QString pasta,QString descricao,QString tipo)
{
    nomePagina = nome;
    pastaPagina = pasta;
    tipoDePagina = tipo;
    descricaoPagina = descricao;
}

/*!
 * \brief Pagina::Pagina is one of the Foto class constructor.
 * \param nome is the Page's name.
 * \param pasta is the Page's directory.
 * \param descricao is the page's description
 * \param tipo is the type of the page
 * \param tipoDeF is the type of party
 * \param data is the date of the page
 */
Pagina::Pagina(QString nome, QString pasta, QString descricao, QString tipo, QString tipoDeF, QDate data)
{
    nomePagina = nome;
    pastaPagina = pasta;
    tipoDePagina = tipo;
    descricaoPagina = descricao;
    dataPagina = data;
    tipoDeFesta = tipoDeF;
}

/*!
 * \brief Pagina::Pagina is one of the Foto class constructor.
 * \param nome is the Page's name.
 * \param pasta is the Page's directory.
 * \param descricao is the page's description
 * \param tipo is the type of the page
 * \param dataI is the initial date of the page
 * \param dataF is the ending date of the page
 */
Pagina::Pagina(QString nome,QString pasta,QString descricao,QString tipo, QDate dataI, QDate dataF)
{
    nomePagina = nome;
    pastaPagina = pasta;
    tipoDePagina = tipo;
    descricaoPagina = descricao;
    dataFimPagina = dataF;
    dataInicioPagina = dataI;
}

/*!
 * \brief Pagina::Pagina is one of the Foto class constructor.
 * \param nome is the Page's name.
 * \param pasta is the Page's directory.
 * \param tipo is the type of the page
 * \param tipoDeF is the type of the page
 * \param descricao is the page's description
 * \param dataInicio is the initial date of the page
 * \param dataFim is the ending date of the page
 * \param dataP is the date of the page
 */
Pagina::Pagina(QString nome, QString pasta, QString tipo, QString tipoDeF, QString descricao,QDate dataInicio,QDate dataFim,QDate dataP)
{
    nomePagina = nome;
    pastaPagina = pasta;
    tipoDePagina = tipo;
    descricaoPagina = descricao;
    tipoDeFesta = tipoDeF;
    dataFimPagina = dataFim;
    dataInicioPagina = dataInicio;
    dataPagina=dataP;

}

/*!
 * \brief Pagina::getNomePagina returns the name of the page
 */
QString Pagina::getNomePagina()
{
    return nomePagina;
}

/*!
 * \brief Pagina::getPastaPagina returns the directory of the page
 */
QString Pagina::getPastaPagina()
{
    return pastaPagina;
}

/*!
 * \brief Pagina::getDescricaoPagina returns the description of the page
 */
QString Pagina::getDescricaoPagina()
{
    return descricaoPagina;
}

/*!
 * \brief Pagina::getTipoDePagina returns the type of the page
 */
QString Pagina::getTipoDePagina()
{
    return tipoDePagina;
}

/*!
 * \brief Pagina::getDataInicioPagina returns the initial date of the page
 */
QDate Pagina::getDataInicioPagina()
{
    return dataInicioPagina;
}
/*!
 * \brief Pagina::getDataFimPagina returns the ending date of the page
 */
QDate Pagina::getDataFimPagina()
{
    return dataFimPagina;
}
/*!
 * \brief Pagina::getTipoDeFesta returns the type of party of the page
 */
QString Pagina::getTipoDeFesta()
{
    return tipoDeFesta;
}
/*!
 * \brief Pagina::getDataPagina returns the date of the page
 */
QDate Pagina::getDataPagina()
{
    return dataPagina;
}
/*!
 * \brief Pagina::setDataPagina sets the date of the page
 * \param novonome is the new date to be given to the page
 */
void Pagina::setPasta(QString novonome)
{
    this->pastaPagina=novonome;
}

/*!
 * \brief Pagina::setDataInicial sets the inicial date of the page
 * \param dataInicial e the date to be given to the page
 */
void Pagina::setDataInicial(QDate dataInicial)
{
    this->dataInicioPagina=dataInicial;
}
/*!
 * \brief Pagina::setDataFinal sets the final date of the page
 * \param dataFinal is the date to be given to the page
 */
void Pagina::setDataFinal(QDate dataFinal)
{
    this->dataFimPagina=dataFinal;
}
