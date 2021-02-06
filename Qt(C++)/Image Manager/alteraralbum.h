#ifndef ALTERARALBUM_H
#include <QDialog>
#include "album.h"
#include "ficheiros.h"
#include <QMessageBox>
#include <QDir>
#include <QString>
#define ALTERARALBUM_H


namespace Ui {
class AlterarAlbum;
}
extern QList <Album*> ListaAlbum;
extern Ficheiros F;

class AlterarAlbum : public QDialog
{
    Q_OBJECT

public:
    explicit AlterarAlbum(int, QWidget *parent = 0);
    ~AlterarAlbum();
private:
    int index;

private slots:
    void on_cancelar_clicked();
    void enable_alterar();
    void on_nome_textChanged();
    void on_Descricao_textChanged();
    void on_ok_clicked();
    QString limparNome(QString str);

private:
    Ui::AlterarAlbum *ui;
};


#endif // ALTERARALBUM_H
