#include "slideshow.h"
#include "ui_slideshow.h"
//==============================================================================================
SlideShow::SlideShow(Pagina *pagina,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlideShow)
{
    ui->setupUi(this);
    slides = pagina;
    ui->radioButton->setDisabled(true);
    ui->radioButton_2->setChecked(true);
}
//==============================================================================================
SlideShow::SlideShow(Album *album,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlideShow)
{
    ui->setupUi(this);
    slides2 = album;
    ui->radioButton_2->setDisabled(true);
    ui->radioButton->setChecked(true);
}
//==============================================================================================
SlideShow::~SlideShow()
{
    delete ui;
}
//==============================================================================================
void SlideShow::on_pushButton_3_clicked()//Abrir ficheiro Audio
{
    QString file = QFileDialog::getOpenFileName(
                this,
                "Abrir",
                "C://",
                "Ficheiro audio (*.mp3)"
                );
     if(!file.isEmpty())
     {
         ui->lineEdit->setText(file);
         fichmp3 = file;
     }
}
//==============================================================================================
void SlideShow::on_pushButton_clicked()//Começar
{
    int intervalo = (int)(ui->doubleSpinBox->value()*1000+0.5);
    if(ui->radioButton_2->isChecked())//so esta pagina
    {
        if(slides->ListaFotos.count()==0)
        {
            QMessageBox::critical(this, "ERRO!", "A página selecionada nao contém fotos");
        }
        else
        {
            SlideViewer *sv = new SlideViewer(fichmp3,slides,intervalo,0);
            sv->exec();
        }
    }
    else if(ui->radioButton->isChecked())//so este album
    {
        int i;
        for(i = 0; i<slides2->ListaPagina.count();i++)
        {
            if(slides2->ListaPagina.at(i)->ListaFotos.count()>0)
                break;
        }
        if(i == slides2->ListaPagina.count())
        {
            QMessageBox::critical(this, "ERRO!", "O album selecionado nao contém fotos");
        }
        else
        {
            SlideViewer *sv = new SlideViewer(fichmp3,slides2,intervalo,0);
            sv->exec();
        }
    }
    else if(ui->radioButton_3->isChecked())//todos os albuns
    {
        SlideViewer *sv = new SlideViewer(fichmp3,intervalo,0);
        sv->exec();
    }
}
//==============================================================================================
void SlideShow::on_pushButton_2_clicked()//Cancelar
{
    this->close();
}
