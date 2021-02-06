/*!
 * \file pessoa.cpp Definitions of the methods of the class Pessoa
 */
//=============================================================================
#include "pessoa.h"

/*!
 * \brief Pessoa::getNomePessoa returns the name of the person
 */
QString Pessoa::getNomePessoa()
{
    return this->nomePessoa;
}
//=============================================================================
/*!
 * \brief Pessoa::getGenero returns the gender of the person
 */
QString Pessoa::getGenero()
{
    return this->genero;
}
//=============================================================================
/*!
 * \brief Pessoa::getDataNascimento returns the birthdate of the person
 */
QDate Pessoa::getDataNascimento()
{
    return this->dataNascimento;
}
//=============================================================================
/*!
 * \brief Pessoa::getRelacao returns the relation between a person and the user
 */
QString Pessoa::getRelacao()
{
    return this->relacao;
}
//=============================================================================
/*!
 * \brief Pessoa::setNomePessoa sets the name of the person
 * \param nome is the name to be given to the person
 */
void Pessoa::setNomePessoa(QString nome)
{
    this->nomePessoa = nome;
}
//=============================================================================
/*!
 * \brief Pessoa::setGenero sets the gender of the person
 * \param genero is the gender to be given to the person
 */
void Pessoa::setGenero(QString genero)
{
    this->genero = genero;
}
//=============================================================================
/*!
 * \brief Pessoa::setDataNascimento sets the birthdate of the person
 * \param data is the birthdate to be given to the person
 */
void Pessoa::setDataNascimento(QDate data)
{
    this->dataNascimento = data;
}
//=============================================================================
/*!
 * \brief Pessoa::setRelacao sets the relation between a person and the user
 * \param relacao is the type of relation
 */
void Pessoa::setRelacao(QString relacao)
{
    this->relacao = relacao;
}
//=============================================================================
/*!
 * \brief Pessoa::Pessoa is the default constructor of the class Pessoa
 * \param nome is the person's name.
 * \param data is the person's birthdate
 * \param genero is the person's gender
 * \param relacao is the relation between the person and the user
 */
Pessoa::Pessoa(QString nome, QDate data, QString genero, QString relacao)
{
    this->nomePessoa = nome;
    this->genero = genero;
    this->dataNascimento = data;
    this->relacao = relacao;
}
//=============================================================================
/*void ListaPessoas::inserePessoa(QString nome, QString genero, QDate data, QString relacao)
{
    Pessoa* novo = new Pessoa;
    novo->setNomePessoa(nome);
    novo->setGenero(genero);
    novo->setDataNascimento(data);
    novo->setRelacao(relacao);
    Pessoa *atual;
    int a;


    if(cabecaPessoa == NULL)
    {
        cabecaPessoa=novo;
    }

    else
    {
        atual=cabecaPessoa;
        QString NovoNome = novo->getNomePessoa();
        QString AtualNome = atual->getNomePessoa();
        a= QString::compare(NovoNome, AtualNome, Qt::CaseInsensitive);

        if(a<0)
        {
            cabecaPessoa = novo;
            novo->proximo = atual;
        }

        else
        {
            while(atual->proximo!=NULL)
            {
                NovoNome = novo->getNomePessoa();
                AtualNome = atual->proximo->getNomePessoa();
                a= QString::compare(NovoNome, AtualNome, Qt::CaseInsensitive);
                if(a<0)
                {
                    break;
                }
                atual=atual->proximo;
            }
            novo->proximo=atual->proximo;
            atual->proximo=novo;
        }



    }

}
//=============================================================================
void ListaPessoas::alteraDados(QString aux, QString nome, QString genero, QDate data, QString relacao)
{
    Pessoa *atual, *aux2, *anterior;
    int a;
    anterior = NULL;
    aux2=NULL;
    atual=cabecaPessoa;
    QString AtualNome;

    while(atual!=NULL)
    {
        AtualNome = atual->getNomePessoa();
        a= QString::compare(AtualNome, aux, Qt::CaseInsensitive);
        if(a==0)
        {
            aux2=atual;
            atual->setNomePessoa(nome);
            atual->setGenero(genero);
            atual->setRelacao(relacao);
            atual->setDataNascimento(data);

            if(anterior==NULL)
                cabecaPessoa=atual->proximo;
            else
                anterior->proximo = atual->proximo;
            break;
        }
        anterior = atual;
        atual=atual->proximo;
    }

    atual=cabecaPessoa;
    AtualNome = atual->getNomePessoa();
    QString Aux2nome = aux2->getNomePessoa();
    a= QString::compare(Aux2nome, AtualNome, Qt::CaseSensitive);

    if(a<0)
    {
        cabecaPessoa = aux2;
        aux2->proximo = atual;
    }

    else
    {
        while(atual->proximo!=NULL)
        {
            Aux2nome = aux2->getNomePessoa();
            QString AtualProximoNome = atual->proximo->getNomePessoa();
            a= QString::compare(Aux2nome, AtualProximoNome, Qt::CaseInsensitive);
            if(a<0)
            {
                break;
            }
            atual=atual->proximo;
        }
        aux2->proximo=atual->proximo;
        atual->proximo=aux2;
    }

}*/
