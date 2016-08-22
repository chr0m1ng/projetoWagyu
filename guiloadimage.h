#ifndef GUILOADIMAGE_H
#define GUILOADIMAGE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QScrollArea>
#include <QLabel>
#include "imgloader.h"

namespace Ui {
class GUILoadImage;
}

class GUILoadImage : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUILoadImage(QWidget *parent = 0);
    ~GUILoadImage();
    ImgLoader* getLoader();
    int getLargura();
    int getAltura();
    int getNc();

private:
    Ui::GUILoadImage *ui;
    ImgLoader *loader = NULL;

    int largura;
    int altura;
    int nc;

private slots:
    void slotGetCaminho();

};

#endif // GUILOADIMAGE_H
