#include "alteraralbum.h"
#include "ui_alteraralbum.h"

AlterarAlbum::AlterarAlbum(int i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlterarAlbum)
{
    ui->setupUi(this);

    index = i;

    ui->DescricaoVelha->setText(ListaAlbum.at(index)->getDescricao());
    ui->nomeVelho->setText(ListaAlbum.at(index)->getNome());

    ui->ok->setEnabled(false);
}
//=========================================================================================
AlterarAlbum::~AlterarAlbum()
{
    delete ui;
}
//=========================================================================================
void AlterarAlbum::on_cancelar_clicked()//Cancelar
{
    this->close();
}
//=========================================================================================
void AlterarAlbum::enable_alterar()
{
    if(!ui->nome->text().isEmpty() || !ui->Descricao->text().isEmpty())
    {
        ui->ok->setEnabled(true);
    }
    else
    {
        ui->ok->setEnabled(false);
    }
}
//=========================================================================================
void AlterarAlbum::on_nome_textChanged()
{
    AlterarAlbum::enable_alterar();
}
//=========================================================================================
void AlterarAlbum::on_Descricao_textChanged()
{
    AlterarAlbum::enable_alterar();
}
//=========================================================================================
void AlterarAlbum::on_ok_clicked()
{
    if(!ui->nome->text().isEmpty())
    {
        bool existe = 0;
        for(int j = 0; j<ListaAlbum.count();j++)
        {
            if(ListaAlbum.at(j)->getNome() == ui->nome->text())
            {
                existe = 1;
                //Message box critical
                QMessageBox::critical(this, "ERRO!", "Já existe um album com o mesmo nome!");
                break;
            }
        }

        if(!existe)
        {

            QString ret = limparNome(ui->nome->text());

            QString localizacaoVelha = ListaAlbum.at(index)->getPasta();
            QString nome = ListaAlbum.at(index)->getNome();
            QString localizacaoNova = localizacaoVelha;
            int n = nome.size();
            localizacaoNova.chop(n);

            localizacaoNova+=ret;

            QDir sa;
            if(!sa.exists(localizacaoNova))
            {
                sa.rename(localizacaoVelha,localizacaoNova);
                ListaAlbum.at(index)->setNome(ui->nome->text());
                ListaAlbum.at(index)->setPasta(localizacaoNova);

                for(int g=0; g < ListaAlbum.at(index)->ListaPagina.count(); g++)
                {
                    QString pasta = ListaAlbum.at(index)->ListaPagina.at(g)->getPastaPagina();
                    pasta.remove(localizacaoVelha, Qt::CaseInsensitive);
                    QString novaPasta = localizacaoNova;
                    novaPasta += pasta;

                    ListaAlbum.at(index)->ListaPagina.at(g)->setPasta(novaPasta);

                    for(int f=0; f < ListaAlbum.at(index)->ListaPagina.at(g)->ListaFotos.count(); f++)
                    {
                        QString pastaFoto = novaPasta;
                        QString nomeFoto = ListaAlbum.at(index)->ListaPagina.at(g)->ListaFotos.at(f)->getNomeFoto();

                        pastaFoto += "/";
                        pastaFoto += nomeFoto;

                        ListaAlbum.at(index)->ListaPagina.at(g)->ListaFotos.at(f)->setDirectorioFoto(pastaFoto);
                    }

                }

                F.escreverAlbuns(ListaAlbum);
                F.escreverPaginas(ListaAlbum);
            }
            else
            {
                QMessageBox::critical(this, "ERRO!", "Já existe uma pasta nesse directorio com o mesmo nome!");
            }
        }
    }

    if(!ui->Descricao->text().isEmpty())
    {
        ListaAlbum.at(index)->setDescricao(ui->Descricao->text());
        F.escreverAlbuns(ListaAlbum);
    }

    this->close();

}
//=========================================================================================
QString AlterarAlbum::limparNome(QString str)
{
    str.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
    str = str.trimmed();
    str.replace(" ","_");
    QString diacriticLetters;
    QStringList noDiacriticLetters;

    if (diacriticLetters.isEmpty()) {
            diacriticLetters = QString::fromUtf8("ŠŒŽšœžŸ¥µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿ");
            noDiacriticLetters << "S"<<"OE"<<"Z"<<"s"<<"oe"<<"z"<<"Y"<<"Y"<<"u"<<"A"<<"A"<<"A"<<"A"<<"A"<<"A"<<"AE"<<"C"<<"E"<<"E"<<"E"<<"E"<<"I"<<"I"<<"I"<<"I"<<"D"<<"N"<<"O"<<"O"<<"O"<<"O"<<"O"<<"O"<<"U"<<"U"<<"U"<<"U"<<"Y"<<"s"<<"a"<<"a"<<"a"<<"a"<<"a"<<"a"<<"ae"<<"c"<<"e"<<"e"<<"e"<<"e"<<"i"<<"i"<<"i"<<"i"<<"o"<<"n"<<"o"<<"o"<<"o"<<"o"<<"o"<<"o"<<"u"<<"u"<<"u"<<"u"<<"y"<<"y";
        }

        QString output = "";
        for (int i = 0; i < str.length(); i++) {
            QChar c = str[i];
            int dIndex = diacriticLetters.indexOf(c);
            if (dIndex < 0)
            {
                output.append(c);
            }
            else
            {
                QString replacement = noDiacriticLetters[dIndex];
                output.append(replacement);
            }
        }

    return output;
}
//=========================================================================================

