#ifndef IMGLOADER_H
#define IMGLOADER_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include "readimage.h"

class ImgLoader : public QWidget
{
    Q_OBJECT
public:
    explicit ImgLoader(QWidget *parent = 0);
    ~ImgLoader();

// Variaveis

    QLabel *imgPreview = NULL;

// Metodos

    QString getCaminho();
    QImage getImgOrig();
    bool isImage();
    void carregarImg(int largura, int altura, int nc);
    unsigned short *getMatrizOrig();

private:
    bool status;
    QString caminho;
    QImage imgOrig;
    tImage st_image;


public slots:

};

#endif // IMGLOADER_H
