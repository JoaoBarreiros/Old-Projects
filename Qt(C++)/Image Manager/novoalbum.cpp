#include "novoalbum.h"
#include "ui_novoalbum.h"


NovoAlbum::NovoAlbum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NovoAlbum)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
}
//=========================================================================================
NovoAlbum::~NovoAlbum()
{
    delete ui;
}
//=========================================================================================
void NovoAlbum::on_pushButton_2_clicked()//Cancelar
{
    this->close();
}
//=========================================================================================
void NovoAlbum::enable_criar()
{
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() && ui->comboBox->currentIndex()>0)
    {
        ui->pushButton->setEnabled(true);
    }
    else
    {
        ui->pushButton->setEnabled(false);
    }
}
//=========================================================================================
void NovoAlbum::on_lineEdit_textChanged()
{
    NovoAlbum::enable_criar();
}
//=========================================================================================
void NovoAlbum::on_lineEdit_2_textChanged()
{
    NovoAlbum::enable_criar();
}
//=========================================================================================
void NovoAlbum::on_comboBox_currentIndexChanged()
{
    NovoAlbum::enable_criar();
}
//=========================================================================================
void NovoAlbum::on_lineEdit_3_textChanged()
{
    NovoAlbum::enable_criar();
}
//=========================================================================================
void NovoAlbum::on_pushButton_clicked()//criar
{
    bool existe = 0;
    for(int i = 0; i<ListaAlbum.count();i++)
    {
        if(ListaAlbum.at(i)->getNome() == ui->lineEdit->text())
        {
            existe = 1;
            //Message box critical
            QMessageBox::critical(this, "ERRO!", "Já existe um album com o mesmo nome!");
            break;
        }
    }

    if(!existe)
    {

        QString ret = limparNome(ui->lineEdit->text());
        QString dir;

        if(ListaAlbum.isEmpty())
        {
            dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        }

        else
        {
            QString localizacao = ListaAlbum.last()->getPasta();
            QString nome = ListaAlbum.last()->getNome();
            int n = nome.size();
            localizacao.chop(n);
            dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), localizacao, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        }


        if(!dir.isEmpty())
        {
            dir+="/";
            dir+=ret;
            QDir sa;
            if(!sa.exists(dir))
            {
                sa.mkpath(dir);
                ListaAlbum.append(new Album(ui->lineEdit->text(),dir,ui->comboBox->currentText(),ui->lineEdit_2->text()));
                F.escreverAlbuns(ListaAlbum);
                this->close();
            }
            else
                QMessageBox::critical(this, "ERRO!", "Já existe uma pasta nesse directorio com o mesmo nome!");
        }
    }
}
//=========================================================================================
QString NovoAlbum::limparNome(QString str)
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
