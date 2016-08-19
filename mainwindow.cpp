#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loader = new ImgLoader;

    ui->IMGPreviewSA->setWidget(loader->imgPreview);

    conexoes(); //Conecta a interface grafica

}

MainWindow::~MainWindow()
{
    delete loader;
    delete ui;
}

void MainWindow::conexoes()
{
    connect(ui->IMGCarregarPB, SIGNAL(released()),this, SLOT(slotCarregarPress())); // Botão de carregar imagem
}

void MainWindow::slotCarregarPress()
{
    largura = ui->LarguraSpinBox->value();
    altura = ui->AlturaSpinBox->value();
    nc = ui->NCspinBox->value();
    loader->carregarImg(largura, altura, nc);
    ui->IMGCaminhoTB->setText(loader->getCaminho());
}
