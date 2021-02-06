#ifndef MAINWINDOW_H
#include <QMainWindow>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QIcon>
#include <QDir>
#include <QDateTime>
#include <QFileInfo>
#include <QMessageBox>
#include <QPixmap>
#include <QDirIterator>
#include <QVariant>
//#include <QPixmapCache>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QCompleter>

#include <QMimeData>
#include <QDragEnterEvent>
#include <QDebug>
#include "configuracaoniveis.h"
#include "associarwindow.h"
#include "acerca.h"
#include "novoalbum.h"
#include "alteraralbum.h"
#include "novapagina.h"
#include "slideshow.h"
#include "imageviewer.h"
#include "perfil.h"
#define MAINWINDOW_H

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAcerca_triggered();
    void on_actionNovo_Album_triggered();
    void on_actionNova_Pagina_triggered();
    //void on_actionEditar_triggered();
    void on_actionAdicionar_Fotografias_triggered();
    void on_actionSlideshow_triggered();
    //void on_remover_clicked();
    void on_fotowidget_itemDoubleClicked(QTableWidgetItem *item);
    void refreshTreeWidget();
    void refreshFotoWidget(Pagina *pagina);
    void refreshListWidget(Pagina *pagina);

    //void dragEnterEvent(QDragEnterEvent *e);
    //void dropEvent(QDropEvent *e);
    void eliminarFotos();
    void eliminarPastaouAlbum();
    void showContextMenuA(const QPoint &pos);
    void showContextMenuF1(const QPoint &pos);
    void showContextMenuF2(const QPoint &pos);

    void on_albumwidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_vistaListaCompleta_clicked();

    void on_vistaMosaico_clicked();
    void calcularDatas();
    void on_vistaListaSimples_clicked();
    void on_actionEditar_triggered();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_actionAdicionar_Pasta_triggered();

    void on_actionAssociar_Pessoas_triggered();
    QTreeWidgetItem* addAlbum(Album *atual);
    void addPagetoAlbum(QTreeWidgetItem *itm,Pagina *pagina);
    void addPhoto(Foto *atual);


    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_returnPressed();

    void on_pessoaWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_fotowidget_itemClicked(QTableWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);
    void MoverPaginaParte1();
    void MoverPaginaParte2();
    void MoverFotosParte1();
    void MoverFotosParte2();
    void CopiarPaginaParte1();
    void CopiarPaginaParte2();
    void CopiarFotosParte1();
    void CopiarFotosParte2();

    QString compararstrdatasInicial(QString str1, QString str2);
    QString compararstrdatasFinal(QString str1, QString str2);

private:
    QList <int> listaIndicesAlbum;
    QList <int> listaIndicesPagina;
    QList <int> listaIndicesFoto;

    bool moverPagina = 0;
    bool copiarPagina = 0;
    int indiceDeAlbum;
    int indiceDePagina;

    bool moverFotos = 0;
    bool copiarFotos = 0;
    int indiceAlbumParaMoverFotos;
    int indicePaginaParaMoverFotos;
    QList <int> indiceFotosParaMoverFotos;

    QList <int> listaIndicesAlbumParaMoverFotos;
    QList <int> listaIndicesPaginaParaMoverFotos;
    QList <int> listaIndicesFotoParaMoverFotos;

    QStringList completionList;
    QCompleter *stringCompleter;

    QPixmap m_pixmap;
    Ui::MainWindow *ui;
    //AssociarWindow *associarwindow = new AssociarWindow();
    Acerca *acercawindow = new Acerca();
    NovoAlbum *novoalbum = new NovoAlbum();
    //NovaPagina *novapagina = new NovaPagina();
    //SlideShow *slideshow = new SlideShow();
    //ImageViewer *imageviewer = new ImageViewer();
};


#endif // MAINWINDOW_H
