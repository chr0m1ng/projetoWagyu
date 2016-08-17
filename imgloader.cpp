#include "imgloader.h"
#include <iostream>


ImgLoader::ImgLoader(QWidget *parent) : QWidget(parent)
{
    isImage = false;

    imgOrig = new QLabel;
    imgOrig->setBackgroundRole(QPalette::Base);
    imgOrig->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imgOrig->setScaledContents(true);
}

ImgLoader::~ImgLoader()
{
    delete imgOrig;
}

void ImgLoader::slotCarregar(int largura, int altura, int nc)
{
    caminho = QFileDialog::getOpenFileName(this, tr("Carregar Arquivo"), QDir::currentPath());
        if(!caminho.isEmpty())
        {
            caminho = "./" + caminho;
            char fileName[32] = {"./D4500.LEFT_CC.raw"};
            ReadImage rImage(fileName, largura, altura);

            st_image = rImage.vectorImage();
            st_image.vi_bits = nc;

            QImage imagem(altura, largura, QImage::Format_RGB16);

            float pix;
            QRgb pixel;

            for(int i = 0; i < altura; i++)
            {
                for(int j = 0; j < largura; j++)
                {
                    pix = (float) st_image.vi_vector[i*altura + j];
                    pixel = qRgb(pix, pix, pix);
                    imagem.setPixel(i, j, pixel);
                }
            }

            if( imagem.isNull() )
            {
                QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar %1.").arg(caminho));
                return;
            }

            imgOrig -> setPixmap(QPixmap::fromImage(imagem));
            imgOrig -> adjustSize();

            isImage = true;
        }
}

QString ImgLoader::getCaminho()
{
    return caminho;
}

short unsigned * ImgLoader::getMatrizOrig()
{
    return st_image.vi_vector;
}
