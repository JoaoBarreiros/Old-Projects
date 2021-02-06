/*!
 * \file foto.h Definitions of the class Foto
 */
#ifndef FOTO_H
#define FOTO_H

#include <QString>
#include <QDate>
#include <QFileInfo>
#include <QPixmap>
#include <QDebug>
#include "pessoa.h"

/*!
 * \brief The Foto class is used represent a photo.
 */
class Foto
{
private:
    /*!
     * \brief directorioFoto is the directory of the photograph.
     */
    QString directorioFoto;
    /*!
     * \brief nomeFoto is the name of the photograph.
     */
    QString nomeFoto;
    /*!
     * \brief resolucaoFoto is the resolution of the photograph.
     */
    QString resolucaoFoto;
    /*!
     * \brief dataFoto is the creation date of the photograph.
     */
    QString dataFoto;
    /*!
     * \brief pix is the pixmap of the photograph.
     */
    QPixmap pix;
    /*!
     * \brief fileInfo contains information about the file that has the photograph.
     */
    QFileInfo fileInfo;

public:
    QList <Pessoa*> ListaPessoas;
    Foto(QString, QString, QString, QString, QFileInfo );
    Foto(QString ,QString , QString ,QString);
//  bool imprimir();
//  bool associarPessoa();
//  bool eliminarPessoa();
//  QString mostrarAssociacoes();
//  Foto(*Foto);
    void setNomeFoto(QString);
    void setDataFoto(QString);
    void setDirectorioFoto(QString);
    void setFileInfo(QFileInfo);
    QString getNomeFoto();
    QString getDataFoto();
    QPixmap getPixFoto();
    QFileInfo getFileInfo();
    QString getResolucaoFoto();
    QString getDirectorioFoto();


};


#endif // FOTO_H
