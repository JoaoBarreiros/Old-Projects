#include "novoperfil.h"
#include "ui_novoperfil.h"

NovoPerfil::NovoPerfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NovoPerfil)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
}
//=========================================================================================
NovoPerfil::~NovoPerfil()
{
    delete ui;
}
//=========================================================================================
void NovoPerfil::on_pushButton_clicked()
{
    bool existe = 0;
    for(int i = 0; i<ListaPessoa.count();i++)
    {
        if(ListaPessoa.at(i)->getNomePessoa() == ui->lineEdit->text())
        {
            existe = 1;
            //Message box critical
            QMessageBox::critical(this, "ERRO!", "Já existe uma pessoa com o mesmo nome!");
            break;
        }
    }

    if(!existe)
    {
        ListaPessoa.append( new Pessoa(ui->lineEdit->text(),ui->dateEdit->date(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
    }


    this->close();

}
//=========================================================================================
void NovoPerfil::on_pushButton_2_clicked()//Cancelar
{
    this->close();
}
//=========================================================================================
void NovoPerfil::on_lineEdit_textChanged()
{
    enable_ok();
}
//=========================================================================================
void NovoPerfil::on_lineEdit_2_textChanged()
{
    enable_ok();
}
//=========================================================================================
void NovoPerfil::on_lineEdit_3_textChanged()
{
    enable_ok();
}
//=========================================================================================
void NovoPerfil::enable_ok()
{
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_3->text().isEmpty())
    {
        ui->pushButton->setEnabled(true);
    }
    else
    {
        ui->pushButton->setEnabled(false);
    }
}
//=========================================================================================
