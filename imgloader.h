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


// Metodos
    QString getCaminho();
    bool getStatus();
    void carregarImg(int largura, int altura, int nc);
    unsigned short *getMatrizOrig();
    QLabel * getImgPreview();

private:

// Variaveis
    QLabel *imgPreview = NULL;
    bool status;
    QString caminho;
    QImage imgOrig;
    tImage st_image;


public slots:

};

#endif // IMGLOADER_H
