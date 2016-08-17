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

    QLabel *imgOrig;
    bool isImage;
    QString getCaminho();
    void slotCarregar(int largura, int altura, int nc);
    unsigned short *getMatrizOrig();

private:
    QString caminho;
    tImage st_image;


public slots:

};

#endif // IMGLOADER_H
