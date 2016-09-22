#include "imgloader.h"
#include <QCoreApplication>
#include <QEventLoop>

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

bool ImgLoader::carregaCaminho()
{
    QPixmap pix("../projetoWagyu/Extras/gifinho.gif");
    if(pix.isNull())
    {
        pix = QPixmap(311, 301);
        QColor color(189,237,2,255);
        pix.fill(color);
    }

    QSplashScreen *spl = new QSplashScreen(pix);
    spl->showMessage("Abrindo...", Qt::AlignCenter, Qt::black);
    spl->setGeometry(x, y, pix.width(), pix.height());


    QString caminho = QFileDialog::getOpenFileName(this, tr("Carregar Arquivo"), QDir::currentPath(), tr("Images (*.1 *.raw)"));
    spl->show();
    spl->raise();
    spl->activateWindow();

    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    int pos = caminho.lastIndexOf("1");
    QString dimensao = caminho;
    dimensao = dimensao.replace(pos, 1, "txt");

    QByteArray ba = dimensao.toLatin1();
    const char *c_str = ba.data();

    std::fstream dim(c_str, std::ios_base::in);

    dim >> largura >> altura;

    if(!this->carregarImg(12, caminho))
    {
        spl->finish(this);
        this->setCaminho(NULL);
        return false;
    }

    spl->finish(this);

    return true;
}

bool ImgLoader::carregarImg(int nc, QString caminho)
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

unsigned short * ImgLoader::getMatrizOrig()
{
    return st_image.vi_vector;
}

int ImgLoader::getLargura()
{
    return largura;
}

int ImgLoader::getAltura()
{
    return altura;
}
