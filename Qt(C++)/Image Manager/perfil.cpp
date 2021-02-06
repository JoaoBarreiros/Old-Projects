#include "perfil.h"
#include "ui_perfil.h"

Perfil::Perfil(int i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Perfil)
{
    ui->setupUi(this);
    index = i;

    QString nome = "Nome: ";
    nome += ListaPessoa.at(index)->getNomePessoa();
    ui->label_2->setText(nome);

    QString genero = "Género: ";
    genero += ListaPessoa.at(index)->getGenero();
    ui->label_4->setText(genero);

    QString relacao = "Relação: ";
    relacao += ListaPessoa.at(index)->getRelacao();
    ui->label_5->setText(relacao);

    QString data = "Data de Nascimento: ";
    data += ListaPessoa.at(index)->getDataNascimento().toString("yyyy.MM.dd");
    ui->label_3->setText(data);

}

Perfil::~Perfil()
{
    delete ui;
}

void Perfil::on_pushButton_clicked()//Botão sair
{
    this->close();
}
