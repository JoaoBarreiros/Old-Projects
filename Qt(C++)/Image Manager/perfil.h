#ifndef PERFIL_H
#include <QDialog>
#include "pessoa.h"

#define PERFIL_H


namespace Ui {
class Perfil;
}

extern QList<Pessoa*> ListaPessoa;

class Perfil : public QDialog
{
    Q_OBJECT

public:
    explicit Perfil(int i, QWidget *parent = 0);
    ~Perfil();
private:
    int index;
private slots:
    void on_pushButton_clicked();

private:
    Ui::Perfil *ui;
};

#endif // PERFIL_H
