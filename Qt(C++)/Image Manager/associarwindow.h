#ifndef ASSOCIARWINDOW_H
#include <QDialog>
#include "pessoa.h"
#include "perfil.h"
#include "novoperfil.h"
#include "ficheiros.h"
#include "novoperfil.h"
#include <QList>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QSet>
#define ASSOCIARWINDOW_H


namespace Ui {
class AssociarWindow;
}
extern QList <Pessoa*> ListaPessoa;
extern Ficheiros F;


class AssociarWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AssociarWindow(int i, int j, QList <int> aux, QList <int> a, QList <int> b, QList <int> c, QWidget *parent = 0);
    ~AssociarWindow();

private:
    int indexAlbum;
    int indexPagina;
    QList <int> indexFoto;
    QList <int> listaIndicesAlbum;
    QList <int> listaIndicesPagina;
    QList <int> listaIndicesFoto;

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void refreshListWidget();
    void refreshListWidget2();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AssociarWindow *ui;

};

#endif // ASSOCIARWINDOW_H
