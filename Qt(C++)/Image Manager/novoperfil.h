#ifndef NOVOPERFIL_H
#include <QDialog>
#include "pessoa.h"
#include <QMessageBox>
#include <QString>
#define NOVOPERFIL_H



namespace Ui {
class NovoPerfil;
}
extern QList<Pessoa*> ListaPessoa;


class NovoPerfil : public QDialog
{
    Q_OBJECT

public:
    explicit NovoPerfil(QWidget *parent = 0);
    ~NovoPerfil();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void enable_ok();
    void on_lineEdit_2_textChanged();
    void on_lineEdit_3_textChanged();
    void on_lineEdit_textChanged();


private:
    Ui::NovoPerfil *ui;
};

#endif // NOVOPERFIL_H
