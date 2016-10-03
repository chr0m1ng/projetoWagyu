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
    if(!nome.isNull())
        QFile::remove(nome);
    delete imgPreview;
}

bool ImgLoader::carregaCaminho(QString caminho)
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

    if(!this->caminho.isEmpty())
    {

        int pos = this->caminho.lastIndexOf("/");

        //Coloca ./ na frente do .raw
        this->caminho.replace(pos, 1, "/./");

        //Conversão de QString para const char *
        QByteArray ba = this->caminho.toLatin1();
        const char *c_str = ba.data();

        ReadImage rImage(c_str, largura, altura);

        st_image = rImage.vectorImage();
        st_image.vi_bits = nc;

       return true;
    }

    else
    {
        QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar caminho %1.").arg(caminho));
        return false;
    }
}

bool ImgLoader::showImage()
{
    if(!this->caminho.isEmpty() && this->nome.isNull())
    {
        //Salva vetor extraido da imagem .raw em um .txt como se fosse um .pgm
        this->nome = this->caminho;
        int pos = nome.lastIndexOf("/");

        nome = nome.remove(0, pos + 1);

        nome.replace(nome.lastIndexOf("."), 2, ".txt");

        QByteArray ba = nome.toLatin1();
        const char *c_str = ba.data();

        FILE *imgRAW = fopen(c_str, "w");
        if(imgRAW == NULL)
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar file 1 %1.").arg(caminho));
            return false;
        }
        fprintf(imgRAW, "P2\n%d %d\n%d\n", altura, largura, (int)pow(2, st_image.vi_bits) - 1);

        for(int i = 0; i < largura; i++)
            for(int j = 0; j < altura; j++)
                fprintf(imgRAW, "%d\n", (int) st_image.vi_vector[i * altura + j]);
        fclose(imgRAW);

        //Converte o .txt para .pgm
        QString pgm = nome;


        pgm = pgm.replace(pgm.lastIndexOf("."), 4, ".pgm");

        std::cout << pgm.toStdString() + " 2"<< std::endl;

        QFile::rename(nome, pgm);

        //Abre e exibe a imagem no formato .pgm

        nome = pgm;

        QImage imagem(nome, "PGM");
        if( imagem.isNull() )
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar 2 %1.").arg(caminho));
            return false;
        }

        imgPreview -> setPixmap(QPixmap::fromImage(imagem));
        imgPreview -> adjustSize();

        imgPreview->setToolTip(nome);

        status = true;


        return true;
    }
    return false;
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

void ImgLoader::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
}
