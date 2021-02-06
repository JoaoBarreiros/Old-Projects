/*!
 * \file pessoa.h Definitions of the class Pessoa
 */
//=============================================================================
#ifndef PESSOA_H
#define PESSOA_H
#include <QApplication>
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QList>
#include <math.h>
#include <QDataStream>
#include <QTextStream>
#include <QDebug>

//=============================================================================
/*!
 * \brief The Pessoa class is used to represent a person.
 */
//=============================================================================
class Pessoa {

private:
    /*!
     * \brief nomePessoa is the person's name.
     */
    QString nomePessoa;
    /*!
     * \brief dataNascimento is the person's date of birth.
     */
    QDate dataNascimento;
    /*!
     * \brief genero is the person's gender.
     */
    QString genero;
    /*!
     * \brief relacao is the person's relation to the user.
     */
    QString relacao;

public:
    Pessoa(QString,QDate,QString,QString);
    QString getNomePessoa();
    QString getGenero();
    QDate getDataNascimento();
    QString getRelacao();
    void setNomePessoa(QString);
    void setGenero(QString);
    void setDataNascimento(QDate);
    void setRelacao(QString);


};
//=============================================================================
#endif // PESSOA_H


