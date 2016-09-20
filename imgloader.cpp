#include "imgloader.h"
#include <stdio.h>
#include <math.h>

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

bool ImgLoader::carregarImg(int largura, int altura, int nc, QString caminho)
{
    this->caminho = caminho;

    if(!caminho.isEmpty())
    {
        //Coloca ./ na frente do .raw
        int pos = caminho.lastIndexOf("/");
        caminho.replace(pos, 1, "/./");

        //Conversão de QString para const char *
        QByteArray ba = caminho.toLatin1();
        const char *c_str = ba.data();

        ReadImage rImage(c_str, largura, altura);

        st_image = rImage.vectorImage();
        st_image.vi_bits = nc;

        //Salva vetor extraido da imagem .raw em um .txt como se fosse um .pgm
        FILE *imgRAW = fopen("imgRAW.txt", "w");
        if(imgRAW == NULL)
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar file %1.").arg(caminho));
            return false;
        }
        fprintf(imgRAW, "P2\n%d %d\n%d\n", altura, largura, (int)pow(2, nc) - 1);
        for(int i = 0; i < largura; i++)
            for(int j = 0; j < altura; j++)
                fprintf(imgRAW, "%d\n", (int) st_image.vi_vector[i * altura + j]);
        fclose(imgRAW);

        //Converte o .txt para .pgm
        QFile::rename("imgRAW.txt", "newImgRAW.pgm");

        //Abre e exibe a imagem no formato .pgm
        QImage imagem("newImgRAW.pgm", "PGM");
        if( imagem.isNull() )
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar %1.").arg(caminho));
            return false;
        }

        imgPreview -> setPixmap(QPixmap::fromImage(imagem));
        imgPreview -> adjustSize();
        QString imgNome = caminho.remove(0, pos + 3);

        imgPreview->setToolTip(imgNome);

        status = true;
        QFile::remove("newImgRAW.pgm");


        return true;
    }

    else
    {
        QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar caminho %1.").arg(caminho));
        return false;
    }
}

QLabel * ImgLoader::getImgPreview()
{
    return imgPreview;
}

QString ImgLoader::getCaminho()
{
    return caminho;
}

bool ImgLoader::getStatus()
{
    return status;
}

void ImgLoader::setCaminho(QString caminho)
{
    this->caminho = caminho;
}

short unsigned * ImgLoader::getMatrizOrig()
{
    return st_image.vi_vector;
}
