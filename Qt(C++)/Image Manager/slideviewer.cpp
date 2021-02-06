#include "slideviewer.h"
#include "ui_slideviewer.h"
//==============================================================================================
SlideViewer::SlideViewer(QString ficheiro, Pagina *atual,int intervalo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlideViewer)
{
    ui->setupUi(this);
    fichmp3 = ficheiro;
    pagina = atual;

    pixmap.load(atual->ListaFotos.first()->getDirectorioFoto());
    indexF++;
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(ficheiro));
    player->setVolume(50);
    player->play();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(intervalo);
}
//==============================================================================================
SlideViewer::SlideViewer(QString ficheiro,Album *atual2 ,int intervalo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlideViewer)
{
    ui->setupUi(this);
    fichmp3 = ficheiro;
    album = atual2;

    while(album->ListaPagina.at(indexP)->ListaFotos.count() == 0)
    {
        indexP++;
    }

    pixmap.load(album->ListaPagina.at(indexP)->ListaFotos.first()->getDirectorioFoto());
    indexF++;

    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(ficheiro));
    player->setVolume(50);
    player->play();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update2()));
    timer->start(intervalo);
}
//==============================================================================================
SlideViewer::SlideViewer(QString ficheiro, int intervalo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlideViewer)
{
    ui->setupUi(this);
    fichmp3 = ficheiro;

    while(indexA<ListaAlbum.count() )
    {
        if(ListaAlbum.at(indexA)->ListaPagina.isEmpty())
            indexA++;
        else
            break;
    }
    if(indexA<ListaAlbum.count())
    {
        player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(ficheiro));
        player->setVolume(50);
        player->play();
        SlideViewer::update3();
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update3()));
        timer->start(intervalo);
    }
}
//==============================================================================================
SlideViewer::~SlideViewer()
{
    delete ui;
}
//==============================================================================================
void SlideViewer::closeEvent(QCloseEvent *event)
{
    player->stop();
    QWidget::closeEvent(event);
}
//==============================================================================================
void SlideViewer::showEvent(QShowEvent *)
{
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    ui->graphicsView->show();
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}
//==============================================================================================
void SlideViewer::resizeEvent(QResizeEvent* event)
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}
//==============================================================================================
void SlideViewer::update()
{
    if(indexF<pagina->ListaFotos.count())
    {
        scene->clear();
        pixmap.load(pagina->ListaFotos.at(indexF)->getDirectorioFoto());
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
        ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
        indexF++;
    }
    else
    {
    }
}
//==============================================================================================
void SlideViewer::update2()
{
    if(indexP<album->ListaPagina.count())
    {
        if(indexF<album->ListaPagina.at(indexP)->ListaFotos.count())
        {
            scene->clear();
            pixmap.load(album->ListaPagina.at(indexP)->ListaFotos.at(indexF)->getDirectorioFoto());
            scene->addPixmap(pixmap);
            ui->graphicsView->setScene(scene);
            ui->graphicsView->show();
            ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
            indexF++;
        }
        else
        {
            indexP++;
            while(indexP<album->ListaPagina.count() )
            {
                if(album->ListaPagina.at(indexP)->ListaFotos.isEmpty())
                    indexP++;
                else
                    break;
            }
            indexF = 0;
            if(indexP<album->ListaPagina.count())
            {
                scene->clear();
                pixmap.load(album->ListaPagina.at(indexP)->ListaFotos.at(indexF)->getDirectorioFoto());
                scene->addPixmap(pixmap);
                ui->graphicsView->setScene(scene);
                ui->graphicsView->show();
                ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
                indexF++;
            }
        }
    }
}
//==============================================================================================
void SlideViewer::update3()
{
    if(indexA<ListaAlbum.count())
    {
        if(indexP<ListaAlbum.at(indexA)->ListaPagina.count())
        {
            album = ListaAlbum.at(indexA);
            SlideViewer::update2();
        }
        else
        {
            indexA++;
            while(indexA<ListaAlbum.count() )
            {
                if(ListaAlbum.at(indexA)->ListaPagina.isEmpty())
                    indexA++;
                else
                {
                    indexP = 0;
                    while(indexP<ListaAlbum.at(indexA)->ListaPagina.count())
                    {
                        if(ListaAlbum.at(indexA)->ListaPagina.at(indexP)->ListaFotos.isEmpty())
                            indexP++;
                        else
                            goto next;
                    }
                    if(indexP == ListaAlbum.at(indexA)->ListaPagina.count())
                    {
                        indexA++;
                        indexP = 0;
                    }
                }
            }
            next:
            if(indexA<ListaAlbum.count())
            {
                indexP = 0;
                indexF = 0;
                album = ListaAlbum.at(indexA);
                SlideViewer::update2();
            }
        }
    }
}
