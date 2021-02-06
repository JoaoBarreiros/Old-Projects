#ifndef IMAGEVIEWER_H
#include <QDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QPixmap>
#include <QFileInfo>
#include <QDateTime>
#include <QPrinter>
#include <QPrintDialog>
#define IMAGEVIEWER_H



namespace Ui {
class ImageViewer;
}

class ImageViewer : public QDialog
{
    Q_OBJECT

public:
    explicit ImageViewer(QString loc,QWidget *parent = 0);
    ~ImageViewer();

private slots:
    void on_pushButton_clicked();
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent *);



private:
    QPixmap pixmap;
    Ui::ImageViewer *ui;
    QGraphicsScene *scene =  new QGraphicsScene;
};

#endif // IMAGEVIEWER_H
