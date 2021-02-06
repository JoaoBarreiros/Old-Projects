#include "mainwindow.h"
#include <QApplication>
#include "ficheiros.h"
#include "pessoa.h"
#include "album.h"
#include <QDebug>

MainWindow *w;
QList <Album*> ListaAlbum;
QList <Pessoa*> ListaPessoa;
Ficheiros F;

int main(int argc, char *argv[])
{
    F.inicializar(ListaAlbum,ListaPessoa);

    QApplication a(argc, argv);
    w = new MainWindow();
    w->show();
    return a.exec();
}
