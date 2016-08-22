#include "guiloadimage.h"
#include "ui_guiloadimage.h"

GUILoadImage::GUILoadImage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUILoadImage)
{
    ui->setupUi(this);
    loader = new ImgLoader;
    connect(ui->pBOpen, SIGNAL(released()), this, SLOT(slotGetCaminho()));
}

GUILoadImage::~GUILoadImage()
{
    delete loader;
    delete ui;
}

ImgLoader* GUILoadImage::getLoader()
{
    return loader;
}

void GUILoadImage::slotGetCaminho()
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
        loader->carregarImg(largura, altura, nc);
        ui->lineCaminho->setText(loader->getCaminho());
        this->close();
    }
}

int GUILoadImage::getLargura()
{
    return largura;
}

int GUILoadImage::getAltura()
{
    return altura;
}

int GUILoadImage::getNc()
{
    return nc;
}
