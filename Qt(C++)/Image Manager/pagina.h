/*!
 * \file pagina.h Definitions of the class Pagina
 */
#ifndef PAGINA_H
#include <QString>
#include <QDate>
#include "foto.h"
#include "pessoa.h"
#define PAGINA_H

/*!
 * \brief The Pagina class is used to represent a page.
 */
class Pagina
{
private:
    /*!
     * \brief nomePagina is the page's name.
     */
    QString nomePagina;
    /*!
     * \brief pastaPagina is the name of the folder that contains the page.
     */
    QString pastaPagina;
    /*!
     * \brief tipoDePagina is the page's type.
     */
    QString tipoDePagina;
    /*!
     * \brief tipoDeFesta is the party type.
     */
    QString tipoDeFesta;
    /*!
     * \brief descricaoPagina is the page's description.
     */
    QString descricaoPagina;
    /*!
     * \brief dataInicio is the oldest photo's date.
     */
    QDate dataInicioPagina;
    /*!
     * \brief dataFim is the newest photo's date.
     */
    QDate dataFimPagina;
    /*!
     * \brief dataPagina is the date of an event that is related to the type of page.
     */
    QDate dataPagina;


public:
    QList <Foto*> ListaFotos;
    QList <Pessoa*> ListaPessoas;
    Pagina(QString,QString,QString,QString);
    Pagina(QString,QString,QString,QString,QString,QDate);
    Pagina(QString,QString,QString,QString,QDate,QDate);
    Pagina(QString, QString, QString, QString, QString,QDate,QDate,QDate);
    void adicionarFoto();
    void removerFoto();
    bool associarPessoaPagina();
    bool eliminarPessoaPagina();
    //void cortarFoto();
    //void colarFoto();
    //void organizarData();
    //void organizarNome();
    //void setDescricaoPagina();
    //void setNomePagina();
    QString getNomePagina();
    QDate getDataInicioPagina();
    QDate getDataFimPagina();
    QString getPessoaPagina();
    void pesquisarPagina();
    QString getPastaPagina();
    QString getTipoDePagina();
    QString getDescricaoPagina();
    QString getTipoDeFesta();
    QDate getDataPagina();
    void setPasta(QString);
    void setDataInicial(QDate);
    void setDataFinal(QDate);



};

#endif // PAGINA_H
