/*!
 * \file foto.cpp Definitions of the methods of the class Foto
 */
#include "foto.h"

/*!
 * \brief Foto::Foto is one of the Foto class constructor.
 * \param nome is the Photograph's name.
 * \param resolucao is resolution of the photograph
 * \param data is the photograh's date of creation
 * \param pixmap is the Pixmap of the photograph
 * \param info contains information about the file that contains the photograph
 */
Foto::Foto(QString nome, QString directorio, QString resolucao, QString data, QFileInfo info)
{
    directorioFoto = directorio;
    nomeFoto = nome;
    resolucaoFoto = resolucao;
    dataFoto = data;
    fileInfo = info;
}

/*!
 * \brief Foto::Foto is one of the Foto class constructor.
 * \param nome is the Photograph's name.
 * \param resolucao is resolution of the photograph
 * \param data is the photograh's date of creation
 */
Foto::Foto(QString nome,QString directorio, QString resolucao,QString data)
{
    directorioFoto = directorio;
    nomeFoto = nome;
    resolucaoFoto = resolucao;
    dataFoto = data;
 }

/*!
 * \brief Foto::getNomeFoto returns the name of the photograph
 */
QString Foto::getNomeFoto()
{
    return this->nomeFoto;
}

/*!
 * \brief Foto::getDataFoto returns the date of the photograph in QString format
 */
QString Foto::getDataFoto()
{
    return this->dataFoto;
}

/*!
 * \brief Foto::getResolucaoFoto returns the resolution of the photograph in QString format
 */
QString Foto::getResolucaoFoto()
{
    return this->resolucaoFoto;
}

/*!
 * \brief Foto::setNomeFoto sets the name of the photograph
 * \param nome is the name to be given to the photograph
 */
void Foto::setNomeFoto(QString nome)
{
    this->nomeFoto=nome;
}
/*!
 * \brief Foto::setDataFoto sets the date of the photograph
 * \param data is the date to be given to the photograph
 */
void Foto::setDataFoto(QString data)
{
    this->dataFoto=data;
}
/*!
 * \brief Foto::setFileInfo sets the fileInfo of the photograph
 * \param info is the QFileinfo to be given to the photograph
 */
void Foto::setFileInfo(QFileInfo info)
{
    this->fileInfo = info;
}
/*!
 * \brief Foto::getFileInfo returns the fileInfo of the photograph
 */
QFileInfo Foto::getFileInfo()
{
    return this->fileInfo;
}
/*!
 * \brief Foto::getDirectorioFoto returns the current directory of the photograph
 */
QString Foto::getDirectorioFoto()
{
    return this->directorioFoto;
}
/*!
 * \brief Foto::setDirectorioFoto sets the current directory of the photograph
 * \param novoDiretorio is the new directory to be given to the photograph
 */
void Foto::setDirectorioFoto(QString novoDirectorio)
{
    this->directorioFoto = novoDirectorio;
}
