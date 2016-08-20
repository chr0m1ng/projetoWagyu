#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openFile = new GUILoadImage;

    conexoes(); //Conecta a interface grafica

// MENU BAR
    createActions();
    createMenus();

    QString message = tr("Abra uma nova imagem");
    statusBar()->showMessage(message);

// Fim MENU BAR

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::conexoes()
{

}

void MainWindow::slotOpen()
{
    openFile->show();
    loader = openFile->getLoader();
    ui->IMGPreviewSA->setWidget(loader->imgPreview);
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a new file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(slotOpen()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
}
