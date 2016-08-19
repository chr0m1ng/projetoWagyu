#include "guiloadimage.h"
#include "ui_guiloadimage.h"

GUILoadImage::GUILoadImage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUILoadImage)
{
    ui->setupUi(this);
    loader = new ImgLoader;
    ui->pBconfirm->setDisabled(true);

    connect(ui->pBOpen, SIGNAL(released()), this, SLOT(slotGetCaminho()));
    connect(ui->pBconfirm, SIGNAL(released()), this, SLOT(slotConfirm()));
}

GUILoadImage::~GUILoadImage()
{
    delete ui;
}

ImgLoader* GUILoadImage::getLoader()
{
    return loader;
}

void GUILoadImage::slotGetCaminho()
{
    int w = ui->LarguraSpinBox->value();
    int h = ui->AlturaSpinBox->value();
    int gs = ui->NCspinBox->value();

    bool status = ((w > 0) && (h > 0)) && (gs > 0);

    QMessageBox msg;

    if(!status)
    {
        msg.setText("Preencha os campos acima com os valores correspondente a imagem a ser aberta!");
        msg.exec();
    }
    else
    {
        loader->carregarImg(w,h,gs);
        this->caminho = loader->getCaminho();
        ui->lineCaminho->setText(this->caminho);
        ui->pBconfirm->setEnabled(true);
    }
}

void GUILoadImage::slotConfirm()
{
    this->close();
}
