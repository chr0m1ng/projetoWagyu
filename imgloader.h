#ifndef IMGLOADER_H
#define IMGLOADER_H

#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <iostream>
#include <string.h>
#include <QSplashScreen>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <QTime>
#include <QSplashScreen>
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
    bool carregaCaminho();
    bool carregarImg(int nc, QString caminho);
    unsigned short *getMatrizOrig();
    QLabel * getImgPreview();
    void setCaminho(QString caminho);
    int getAltura();
    int getLargura();

    void setXY(int x, int y);

private:

// Variaveis
    QLabel *imgPreview = NULL;
    bool status;
    QString caminho;
    QImage imgOrig;
    tImage st_image;
    int largura;
    int altura;
    int x, y;

public slots:

};

#endif // IMGLOADER_H
