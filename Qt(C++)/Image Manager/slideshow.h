#ifndef SLIDESHOW_H
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "pagina.h"
#include "album.h"
#include "slideviewer.h"
#define SLIDESHOW_H



namespace Ui {
class SlideShow;
}

class SlideShow : public QDialog
{
    Q_OBJECT

public:
    explicit SlideShow(Pagina *pagina, QWidget *parent = 0);
    explicit SlideShow(Album *album, QWidget *parent = 0);
    ~SlideShow();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    int modo;
    Ui::SlideShow *ui;
    Pagina *slides;
    Album *slides2;
    QString fichmp3;
};

#endif // SLIDESHOW_H
