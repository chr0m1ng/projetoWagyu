#include "guiimageloader.h"
#include "ui_guiimageloader.h"
#include <QTime>

GUIImageLoader::GUIImageLoader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIImageLoader)
{
    ui->setupUi(this);
    loader = new ImgLoader;
    connect(ui->pBOpen, SIGNAL(released()), this, SLOT(slotGetCaminho()));
}

GUIImageLoader::~GUIImageLoader()
{
    delete loader;
    delete ui;
}

ImgLoader* GUIImageLoader::getLoader()
{
    return loader;
}

void GUIImageLoader::slotGetCaminho()
{
    largura = ui->LarguraSpinBox->value();
    altura = ui->AlturaSpinBox->value();
    nc = ui->NCspinBox->value();

    bool status = ((altura > 0) && (largura > 0)) && (nc > 0);

    QMessageBox msg;

    if(!status)
    {
        msg.setText("Preencha os campos acima com os valores correspondente a imagem a ser aberta!");
        msg.exec();
    }
    else
    {
        this->close();

        QPixmap pix("../projetoWagyu/Extras/gifinho.gif");
        if(pix.isNull())
        {
            pix = QPixmap(311, 301);
            QColor color(189,237,2,255);
            pix.fill(color);
        }

        QSplashScreen *spl = new QSplashScreen(pix);
        spl->showMessage("Aguarde...", Qt::AlignCenter, Qt::black);
        spl->setGeometry(x, y, pix.width(), pix.height());
        qApp->processEvents(QEventLoop::AllEvents);


        QString caminho = QFileDialog::getOpenFileName(this, tr("Carregar Arquivo"), QDir::currentPath());
        spl->show();
        spl->raise();
        spl->activateWindow();

        QTime dieTime = QTime::currentTime().addMSecs(1000);
        while(QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        loader->carregarImg(largura, altura, nc, caminho);
        ui->lineCaminho->setText(loader->getCaminho());

        spl->finish(this);
    }
}

int GUIImageLoader::getLargura()
{
    return largura;
}

int GUIImageLoader::getAltura()
{
    return altura;
}

int GUIImageLoader::getNc()
{
    return nc;
}
