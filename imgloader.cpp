#include "imgloader.h"
#include <iostream>


ImgLoader::ImgLoader(QWidget *parent) : QWidget(parent)
{
    status = false;

    imgPreview = new QLabel;
    imgPreview->setBackgroundRole(QPalette::Base);
    imgPreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imgPreview->setScaledContents(true);
}

ImgLoader::~ImgLoader()
{
    delete imgPreview;
}

void ImgLoader::carregarImg(int largura, int altura, int nc)
{
    caminho = QFileDialog::getOpenFileName(this, tr("Carregar Arquivo"), QDir::currentPath());
    QMessageBox msg;

    QFile file(caminho);
    if (!file.open(QFile::ReadOnly))
    {
       msg.setText("Falha ao tentar abrir o arquivo!");
       msg.exec();
    }
    else
    {
       QByteArray array =file.readAll();
       unsigned char* Data = (unsigned char*)&array.data()[0];
       QImage img(Data,largura,altura,QImage::Format_RGB16);
       imgOrig = img;
       imgPreview->setPixmap(QPixmap::fromImage(imgOrig));
       imgPreview->adjustSize();

       status = true;
    }


//    if(!caminho.isEmpty())
//    {
//        caminho = "./" + caminho;
//        char fileName[32] = {"./D4500.LEFT_CC.raw"};
//        ReadImage rImage(fileName, largura, altura);

//        st_image = rImage.vectorImage();
//        st_image.vi_bits = nc;

//        QImage imagem(altura, largura, QImage::Format_RGB16);

//        float pix;
//        QRgb pixel;

//        for(int i = 0; i < altura; i++)
//        {
//            for(int j = 0; j < largura; j++)
//            {
//                pix = (float) st_image.vi_vector[i*altura + j];
//                pixel = qRgb(pix, pix, pix);
//                imagem.setPixel(i, j, pixel);
//            }
//        }

//        if( imagem.isNull() )
//        {
//            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar %1.").arg(caminho));
//            return;
//        }

//        imgOrig -> setPixmap(QPixmap::fromImage(imagem));
//        imgOrig -> adjustSize();

//        isImage = true;
//    }
}

QString ImgLoader::getCaminho()
{
    return caminho;
}

QImage ImgLoader::getImgOrig()
{
    return imgOrig;
}

bool ImgLoader::isImage()
{
    return status;
}

short unsigned * ImgLoader::getMatrizOrig()
{
    return st_image.vi_vector;
}
