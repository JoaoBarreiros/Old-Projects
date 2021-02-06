#ifndef SLIDEVIEWER_H
#define SLIDEVIEWER_H
#include <QDialog>
#include <QWidget>
#include <QGraphicsScene>
#include "pagina.h"
#include "album.h"
#include <QPixmap>
#include <QMediaPlayer>
#include <QTimer>

namespace Ui {
class SlideViewer;
}
extern QList <Album*> ListaAlbum;

class SlideViewer : public QDialog
{
    Q_OBJECT

public:
    explicit SlideViewer(QString ficheiro, Pagina *atual, int intervalo, QWidget *parent = 0);
    explicit SlideViewer(QString ficheiro, Album *atual2, int intervalo, QWidget *parent = 0);
    explicit SlideViewer(QString ficheiro, int intervalo, QWidget *parent = 0);
    ~SlideViewer();
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent* event);

private slots:
    void update();
    void update2();
    void update3();


private:
    Ui::SlideViewer *ui;
    QPixmap pixmap;
    QString fichmp3;
    QMediaPlayer *player;
    Pagina *pagina;
    Album *album;
    QGraphicsScene *scene =  new QGraphicsScene;
    int indexA = 0;
    int indexP = 0;
    int indexF = 0;

};

#endif // SLIDEVIEWER_H
