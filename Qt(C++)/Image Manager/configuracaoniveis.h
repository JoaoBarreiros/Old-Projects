#ifndef CONFIGURACAONIVEIS_H
#include <QList>
#include <QDialog>
#include <QDir>
#include <QString>
#include <QDirIterator>
#include "ficheiros.h"
#include "pagina.h"
#include "album.h"
#include "novapagina.h"
#define CONFIGURACAONIVEIS_H

namespace Ui {
class ConfiguracaoNiveis;
}
extern QList <Album*> ListaAlbum;
extern Ficheiros F;


class ConfiguracaoNiveis : public QDialog
{
    Q_OBJECT

public:
    explicit ConfiguracaoNiveis(int i,QString dir, QWidget *parent = 0);
    ~ConfiguracaoNiveis();
private:
    QPixmap m_pixmap;
    QString directorio;
    int index;

private slots:
    void on_Cancelar_clicked();
    void on_OK_clicked();

private:
    Ui::ConfiguracaoNiveis *ui;
};

#endif // CONFIGURACAONIVEIS_H
