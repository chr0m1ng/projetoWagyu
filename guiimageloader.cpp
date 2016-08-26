#include "guiimageloader.h"
#include "ui_guiimageloader.h"

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
    //QMessageBox::warning(this,"Aviso!","Talvez uma mensagem de que o programa parou de responder seja exibida, apenas ignore.",1,0,0);
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
