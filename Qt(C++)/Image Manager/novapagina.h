#ifndef NOVAPAGINA_H
#include <QDialog>
#include "pagina.h"
#include "album.h"
#include "pessoa.h"
#include "ficheiros.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#define NOVAPAGINA_H



namespace Ui {
class NovaPagina;
}
extern QList <Album*> ListaAlbum;
extern QList <Pessoa*> ListaPessoa;
extern Ficheiros F;

class NovaPagina : public QDialog
{
    Q_OBJECT
public:
    explicit NovaPagina(int i, QWidget *parent = 0);
    ~NovaPagina();
private:
    int index;
private slots:
    QString limparNome(QString);
    QString criarNome(QString,QString,QString,QDate,QDate,QDate);
    void on_pushButton_2_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_5_textChanged(const QString &arg1);
    void enable_criar();
    void on_pushButton_clicked();

private:
    Ui::NovaPagina *ui;
};

#endif // NOVAPAGINA_H
