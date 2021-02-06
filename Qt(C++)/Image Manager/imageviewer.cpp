#include "imageviewer.h"
#include "ui_imageviewer.h"

ImageViewer::ImageViewer(QString loc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    pixmap.load(loc);
    QFileInfo fileInfo(loc);
    ui->label_2->setText("Data em que foi tirada:"+fileInfo.lastModified().toString(Qt::DefaultLocaleShortDate));
    ui->label->setText("Resolução:"+QString::number(pixmap.width())+QString("x")+QString::number(pixmap.height()));

}
//===============================================================================
void ImageViewer::showEvent(QShowEvent *)
{
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    ui->graphicsView->show();
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);

}
//===============================================================================
ImageViewer::~ImageViewer()
{
    pixmap.~QPixmap();
    delete ui;
}
//===============================================================================
void ImageViewer::resizeEvent(QResizeEvent* event)
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}
//===============================================================================
void ImageViewer::on_pushButton_clicked()//Imprimir
{
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Imprimir imagem");

    if(dialog->exec() == QDialog::Accepted)
    {
        QPainter painter;
        painter.begin(&printer);
        painter.drawPixmap(QPoint(0,0),pixmap);
        painter.end();
    }
    delete dialog;

}

