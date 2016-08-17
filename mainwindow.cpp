#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loader = new ImgLoader;

    ui->IMGscrollArea->setWidget(loader->imgOrig);


    connect(ui->CarregarPb, SIGNAL(released()),this, SLOT(carregarPress()));

}

MainWindow::~MainWindow()
{
    delete loader;
    delete ui;
}

void MainWindow::carregarPress()
{
    largura = ui->LarguraSpinBox->value();
    altura = ui->AlturaSpinBox->value();
    nc = ui->NCspinBox->value();
    loader->slotCarregar(largura, altura, nc);
    ui->IMGTextB->setText(loader->getCaminho());
}
