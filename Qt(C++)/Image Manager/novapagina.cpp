#include "novapagina.h"
#include "ui_novapagina.h"

NovaPagina::NovaPagina(int i,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NovaPagina)
{
    ui->setupUi(this);
    index = i;

    ui->pushButton->setEnabled(false);

    QObject::connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(reject()));

    QString tipo = ListaAlbum.at(index)->getTipo();

    if(tipo == "Festa")
    {
        ui->lineEdit_2->setDisabled(false);
        ui->dateEdit_3->setDisabled(false);
        ui->dateEdit_2->setDisabled(true);
        ui->dateEdit->setDisabled(true);
    }

    if(tipo == "Viagem" || tipo == "Outro")
    {
        ui->lineEdit_2->setDisabled(true);
        ui->dateEdit_3->setDisabled(true);
        ui->dateEdit_2->setDisabled(false);
        ui->dateEdit->setDisabled(false);
    }
    if(tipo=="Coisa ou Pessoa")
    {
        ui->lineEdit_2->setDisabled(true);
        ui->dateEdit_3->setDisabled(true);
        ui->dateEdit_2->setDisabled(true);
        ui->dateEdit->setDisabled(true);
    }
}
//=========================================================================================
NovaPagina::~NovaPagina()
{
    delete ui;
}
//=========================================================================================
void NovaPagina::on_pushButton_2_clicked()
{
    this->close();
}
//=========================================================================================
void NovaPagina::enable_criar()
{
    QString tipo = ListaAlbum.at(index)->getTipo();
    QString descricao = ui->lineEdit_5->text();
    QString tipoDeFesta = ui->lineEdit_2->text();

    if( ui->lineEdit->text().isEmpty() )
    {
        ui->pushButton->setEnabled(false);
    }
    if( descricao.isEmpty() )
    {
        ui->pushButton->setEnabled(false);
    }
    if( (tipo == "Festa") && tipoDeFesta.isEmpty() )
    {
        ui->pushButton->setEnabled(false);
    }

    if( !ui->lineEdit->text().isEmpty() )
    {
        if( !descricao.isEmpty() )
        {
            if( (tipo == "Festa") && !tipoDeFesta.isEmpty() )
            {
                ui->pushButton->setEnabled(true);
            }
            if( (tipo != "Festa"))
            {
                ui->pushButton->setEnabled(true);
            }
        }
    }
}
//=========================================================================================
void NovaPagina::on_lineEdit_2_textChanged(const QString &arg1)
{
    NovaPagina::enable_criar();
}
//=========================================================================================
void NovaPagina::on_lineEdit_textChanged(const QString &arg1)
{
    NovaPagina::enable_criar();
}
//=========================================================================================
void NovaPagina::on_lineEdit_5_textChanged(const QString &arg1)
{
    NovaPagina::enable_criar();
}
//=========================================================================================
void NovaPagina::on_pushButton_clicked()
{
    bool existe = 0;
    QString tipo = ListaAlbum.at(index)->getTipo();

    QString nome1 = ui->lineEdit->text();

    QString nome2 = criarNome(tipo, ui->lineEdit_5->text(), ui->lineEdit_2->text(), ui->dateEdit->date(), ui->dateEdit_2->date(), ui->dateEdit_3->date());
    nome2 = limparNome(nome2);

    for(int i = 0; i<ListaAlbum.at(index)->ListaPagina.count();i++)
    {
        if(ListaAlbum.at(index)->ListaPagina.at(i)->getNomePagina() == nome1)
        {
            existe = 1;
            //Message box critical
            QMessageBox::critical(this, "ERRO!", "Já existe uma página neste álbum com o mesmo nome!");
            break;
        }
    }
    if(!existe)
    {
        QString pasta = ListaAlbum.at(index)->getPasta();
        pasta+="/";
        pasta+=nome2;

        QDir sa;
        if(!sa.exists(pasta))
        {
            sa.mkpath(pasta);
            if(tipo=="Festa")
            {
                ListaAlbum.at(index)->ListaPagina.append(new Pagina(nome1,pasta,ui->lineEdit_5->text(),tipo));
                //F.escreverPaginas(ListaAlbum,index);
            }

            if(tipo=="Coisa ou Pessoa")
            {
                ListaAlbum.at(index)->ListaPagina.append(new Pagina(nome1,pasta,ui->lineEdit_5->text(),tipo,ui->lineEdit_2->text(),ui->dateEdit_3->date()));
                //F.escreverPaginas(ListaAlbum,index);
            }

            if(tipo=="Viagem" || tipo=="Outro")
            {
                ListaAlbum.at(index)->ListaPagina.append(new Pagina(nome1,pasta,ui->lineEdit_5->text(),tipo,ui->dateEdit->date(),ui->dateEdit_2->date()));
                //F.escreverPaginas(ListaAlbum,index);
            }
            for(int j=0; j<ListaAlbum.at(index)->ListaPessoas.count(); j++)
            {
                ListaAlbum.at(index)->ListaPagina.last()->ListaPessoas.append(ListaAlbum.at(index)->ListaPessoas.at(j));
            }
            F.escreverPaginas(ListaAlbum);
            F.escreverAssociacoes(ListaAlbum,ListaPessoa);
            this->close();
        }
        else
        {
            QMessageBox::critical(this, "ERRO!", "Já existe uma pasta nesse directorio com o mesmo nome! Altere pelo menos um dos campos");
        }

    }
}
//=========================================================================================
QString NovaPagina::limparNome(QString str)
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
QString NovaPagina::criarNome(QString tipo, QString descricao, QString tipoDeFesta, QDate dataInicio, QDate dataFim, QDate data)
{
    QString nome;

    if(tipo=="Festa")
    {
        QString aux = data.toString("ddMMMyyyy");
        nome += aux;
        nome += " ";
        nome += tipoDeFesta;
        nome += " ";
        nome += descricao;
    }

    if(tipo=="Coisa ou Pessoa")
    {
        nome = descricao;
    }

    if(tipo=="Viagem" || tipo=="Outro")
    {
        QString aux = dataInicio.toString("ddMMMyyyy");
        QString aux2 = dataFim.toString("ddMMMyyyy");
        nome += aux;
        nome += " ";
        nome += aux2;
        nome += " ";
        nome += descricao;
    }
    return nome;
}
//=========================================================================================
