#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openFile = new GUILoadImage;
    conexoes(); //Conecta a interface grafica

    ui->extrairPb->setEnabled(false);

// MENU BAR
    createActions();
    createMenus();
// Fim MENU BAR
}

MainWindow::~MainWindow()
{
    delete loader;
    delete openAct;
    delete openFile;
    delete ui;
}

void MainWindow::conexoes()
{
    //Conexão das CheckBox
    connect(ui->SelTodos, SIGNAL(clicked()), this, SLOT(slotSel()));
    connect(ui->ATH01, SIGNAL(clicked()), this, SLOT(slotATH01()));
    connect(ui->ATH02, SIGNAL(clicked()), this, SLOT(slotATH02()));
    connect(ui->ATH03, SIGNAL(clicked()), this, SLOT(slotATH03()));
    connect(ui->ATH04, SIGNAL(clicked()), this, SLOT(slotATH04()));
    connect(ui->ATH05, SIGNAL(clicked()), this, SLOT(slotATH05()));
    connect(ui->ATH06, SIGNAL(clicked()), this, SLOT(slotATH06()));
    connect(ui->ATH07, SIGNAL(clicked()), this, SLOT(slotATH07()));
    connect(ui->ATH08, SIGNAL(clicked()), this, SLOT(slotATH08()));
    connect(ui->ATH09, SIGNAL(clicked()), this, SLOT(slotATH09()));
    connect(ui->ATH10, SIGNAL(clicked()), this, SLOT(slotATH10()));
    connect(ui->ATH11, SIGNAL(clicked()), this, SLOT(slotATH11()));
    connect(ui->ATH12, SIGNAL(clicked()), this, SLOT(slotATH12()));
    connect(ui->ATH13, SIGNAL(clicked()), this, SLOT(slotATH13()));

    connect(ui->extrairPb, SIGNAL(released()), this, SLOT(slotExtracao()));
}

void MainWindow::slotSel()
{
    if(ui->SelTodos->isChecked())
    {
        ui->ATH01->setChecked(true);
        ui->ATH02->setChecked(true);
        ui->ATH03->setChecked(true);
        ui->ATH04->setChecked(true);
        ui->ATH05->setChecked(true);
        ui->ATH06->setChecked(true);
        ui->ATH07->setChecked(true);
        ui->ATH08->setChecked(true);
        ui->ATH09->setChecked(true);
        ui->ATH10->setChecked(true);
        ui->ATH11->setChecked(true);
        ui->ATH12->setChecked(true);
        ui->ATH13->setChecked(true);
    }

    else
    {
        ui->ATH01->setChecked(false);
        ui->ATH02->setChecked(false);
        ui->ATH03->setChecked(false);
        ui->ATH04->setChecked(false);
        ui->ATH05->setChecked(false);
        ui->ATH06->setChecked(false);
        ui->ATH07->setChecked(false);
        ui->ATH08->setChecked(false);
        ui->ATH09->setChecked(false);
        ui->ATH10->setChecked(false);
        ui->ATH11->setChecked(false);
        ui->ATH12->setChecked(false);
        ui->ATH13->setChecked(false);
    }
}

void MainWindow::slotOpen()
{
    openFile->show();
    loader = openFile->getLoader();
    ui->IMGPreviewSA->setWidget(loader->getImgPreview());
    ui->extrairPb->setEnabled(true);
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Abrir"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Carregar uma nova imagem"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(slotOpen()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Arquivo"));
    fileMenu->addAction(openAct);
}

void MainWindow::slotExtracao()
{
    if(loader->getStatus())
    {
        int NG = pow(2, openFile->getNc());
        matrizCoN_CPU = new double[NG * NG];
        ath = new Haralick(loader->getMatrizOrig(), openFile->getLargura(), openFile->getAltura(), openFile->getNc());
        ath->calcularMatrizCoN(matrizCoN_CPU, ui->DMCOspinBox->value());
        ath->atCpu(matrizCoN_CPU, NG);
        if(ui->ATH01->isChecked())
        {
            std::cout << "Energia: " << ath->energia() << std::endl;
        }
    }
}

void MainWindow::slotATH01()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH02()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH03()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH04()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH05()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH06()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH07()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH08()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH09()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH10()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH11()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH12()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
void MainWindow::slotATH13()
{
    if(ui->SelTodos->isChecked())
        ui->SelTodos->setChecked(false);
}
