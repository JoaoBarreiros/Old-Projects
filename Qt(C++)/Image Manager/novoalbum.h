#ifndef NOVOALBUM_H
#include <QDialog>
#include "album.h"
#include "ficheiros.h"
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
//#include "mainwindow.h"
#define NOVOALBUM_H



namespace Ui {
class NovoAlbum;
}
extern Ficheiros F;
extern Album *album;
extern QList <Album*> ListaAlbum;

class NovoAlbum : public QDialog
{
    Q_OBJECT

public:
    explicit NovoAlbum(QWidget *parent = 0);
    ~NovoAlbum();

private slots:
    void on_pushButton_2_clicked();
    void on_lineEdit_textChanged();
    void on_lineEdit_2_textChanged();
    void on_comboBox_currentIndexChanged();
    void on_lineEdit_3_textChanged();
    void enable_criar();
    void on_pushButton_clicked();
    QString limparNome(QString);

private:
    Ui::NovoAlbum *ui;
};

#endif // NOVOALBUM_H
