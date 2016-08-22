#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openFile = new GUILoadImage;

    ui->extrairPb->setEnabled(false);

// MENU BAR
    createActions();
    createMenus();
// Fim MENU BAR
// Cria GUI PRINCIPAL
    createGUI();
    conexoes(); //Conecta a interface grafica
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

    connect(caixasDeSelecao[0], SIGNAL(clicked()), this, SLOT(slotSel()));
    for(int i = 1; i < 14; i++)
        connect(caixasDeSelecao[i], SIGNAL(clicked()), this, SLOT(slotATH()));

    connect(ui->extrairPb, SIGNAL(released()), this, SLOT(slotExtracao()));
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

void MainWindow::createBoxes()
{

    for(int i = 0, h = 30; i < 14; i++, h += 20)
    {
        caixasDeSelecao[i] = new QCheckBox(nomesATH[i], frameATH);
        caixasDeSelecao[i]->setVisible(true);
        caixasDeSelecao[i]->setGeometry(10,h,191,25);
        caixasDeSelecao[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
}

void MainWindow::createGUI()
{
    createPreview();
    createATH();
    createDMCO();
}

void MainWindow::createPreview()
{
    framePreview = new QFrame(this->centralWidget());
    framePreview->setEnabled(true);
    framePreview->setGeometry(20,20,331,331);
    framePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    framePreview->setLineWidth(1);
    framePreview->setFrameShadow(QFrame::Raised);
    framePreview->setFrameShape(QFrame::StyledPanel);
    framePreview->setVisible(true);

    labelPreview = new QLabel(framePreview);
    labelPreview->setText("PREVIEW");
    labelPreview->setGeometry(140,0,71,16);
    labelPreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelPreview->setVisible(true);

    areaPreview = new QScrollArea(framePreview);
    areaPreview->setGeometry(10,20,311,301);
    areaPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    areaPreview->setFrameShadow(QFrame::Sunken);
    areaPreview->setFrameShape(QFrame::StyledPanel);
    areaPreview->setWidgetResizable(true);

}

void MainWindow::createATH()
{
    frameATH = new QFrame(this->centralWidget());
    frameATH->setEnabled(true);
    frameATH->setGeometry(400,20,231,331);
    frameATH->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frameATH->setLineWidth(1);
    frameATH->setFrameShadow(QFrame::Raised);
    frameATH->setFrameShape(QFrame::StyledPanel);
    frameATH->setVisible(true);

    labelATH = new QLabel(frameATH);
    labelATH->setText("ATRIBUTOS DE TEXTURA");
    labelATH->setGeometry(40,0,171,16);
    labelATH->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelATH->setVisible(true);

    createBoxes();
}

void MainWindow::createDMCO()
{
    frameDMCO = new QFrame(this->centralWidget());
    frameDMCO->setEnabled(true);
    frameDMCO->setGeometry(680,20, 241,71);
    frameDMCO->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frameDMCO->setLineWidth(1);
    frameDMCO->setFrameShadow(QFrame::Raised);
    frameDMCO->setFrameShape(QFrame::StyledPanel);
    frameDMCO->setVisible(true);

    labelDMCO = new QLabel(frameDMCO);
    labelDMCO->setText("DISTANCIA MCO");
    labelDMCO->setGeometry(60,0,121,16);
    labelDMCO->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelDMCO->setToolTip("Distancia Matriz de Coocorrencia");
    labelDMCO->setVisible(true);

    caixaDMCO = new QSpinBox(frameDMCO);
    caixaDMCO->setEnabled(true);
    caixaDMCO->setGeometry(40,30,160,30);
    caixaDMCO->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    caixaDMCO->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    caixaDMCO->setKeyboardTracking(true);
    caixaDMCO->setMinimum(1);
    caixaDMCO->setMaximum(99999);
    caixaDMCO->setVisible(true);
}

// SLOTS

void MainWindow::slotOpen()
{
    openFile->show();
    loader = openFile->getLoader();
    areaPreview->setWidget(loader->getImgPreview());
    ui->extrairPb->setEnabled(true);
}

void MainWindow::slotExtracao()
{
    if(loader->getStatus())
    {
        int NG = pow(2, openFile->getNc());
        matrizCoN_CPU = new double[NG * NG];
        ath = new Haralick(loader->getMatrizOrig(), openFile->getLargura(), openFile->getAltura(), openFile->getNc());
        ath->calcularMatrizCoN(matrizCoN_CPU, caixaDMCO->value());
        ath->atCpu(matrizCoN_CPU, NG);
        //results->open();
        if(caixasDeSelecao[1]->isChecked())
        {
            std::cout << "Energia: " << ath->energia() << std::endl;
        }
    }
}

void MainWindow::slotSel()
{
    if(caixasDeSelecao[0]->isChecked())
        for(int i = 1; i < 14; i++)
            caixasDeSelecao[i]->setChecked(true);
    else
        for(int i = 1; i < 14; i++)
            caixasDeSelecao[i]->setChecked(false);
}

void MainWindow::slotATH()
{
    if(caixasDeSelecao[0]->isChecked())
        caixasDeSelecao[0]->setChecked(false);
}
