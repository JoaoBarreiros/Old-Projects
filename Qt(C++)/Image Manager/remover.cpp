#include "remover.h"
#include "ui_remover.h"

Remover::Remover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remover)
{
    ui->setupUi(this);
}

Remover::~Remover()
{
    delete ui;
}
