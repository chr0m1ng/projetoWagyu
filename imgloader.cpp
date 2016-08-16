#include "imgloader.h"

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

void ImgLoader::slotCarregar(int largura, int altura)
{
    caminho = QFileDialog::getOpenFileName(this, tr("Carregar Arquivo"), QDir::currentPath());
        if(!caminho.isEmpty())
        {
            /*
            QFile file(caminho);
            if(!file.open(QFile::ReadOnly))
            {
                QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar %1.").arg(caminho));
                return;
            }
            QByteArray array = file.readAll();*/
            QImage imagem(caminho);
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
