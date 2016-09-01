#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    caixasDeSelecao = new QCheckBox*[14];
    isNovaImg = false;
    boxCheckeds = new bool[14];
    atributosSelecionados = new double[14];

    nomesATH[0] = "Selecionar Todos";
    nomesATH[1] = "Energia";
    nomesATH[2] = "Contraste";
    nomesATH[3] = "Correlação";
    nomesATH[4] = "Variancia";
    nomesATH[5] = "MDI";
    nomesATH[6] = "Media Soma";
    nomesATH[7] = "Variancia Soma";
    nomesATH[8] = "Entropia Soma";
    nomesATH[9] = "Entropia";
    nomesATH[10] = "Variancia Diferença";
    nomesATH[11] = "Entropia Diferença";
    nomesATH[12] = "Medidas Correlação 1";
    nomesATH[13] = "Medidas Correlação 2";


    ui->setupUi(this);
    createGUI();

    ui->extrairPb->setEnabled(false);
    frameATH->setEnabled(false);
    frameDMCO->setEnabled(false);
    frameNT->setEnabled(false);




// MENU BAR
    createActions();
    createMenu();
// Fim MENU BAR

    createConnections(); //Conecta a interface grafica
}

MainWindow::~MainWindow()
{
    delete framePreview;
    delete frameATH;
    delete frameDMCO;
    delete labelPreview;
    delete labelATH;
    delete labelDMCO;
    delete areaPreview;
    delete caixaDMCO;
    delete caixasDeSelecao;
    delete fileMenu;
    delete ath;
    delete loader;
    delete openAct;
    delete openFile;
    delete resultAct;
    delete matrizAct;
    delete [] boxCheckeds;
    delete ui;
}

/*
 *
 *
 *
 * METODOS
 *
 *
 *
 */

void MainWindow::createConnections()
{
    connect(caixasDeSelecao[0], SIGNAL(clicked()), this, SLOT(slotSelectAll()));
    for(int i = 1; i < 14; i++)
        connect(caixasDeSelecao[i], SIGNAL(clicked()), this, SLOT(slotATHs()));

    connect(ui->extrairPb, SIGNAL(released()), this, SLOT(slotExtracao()));

    matriz = new GUIMatrizCoo();
    connect(matriz->getBt(0), SIGNAL(released()), this, SLOT(slotMatrizesCoOc135()));
    connect(matriz->getBt(1), SIGNAL(released()), this, SLOT(slotMatrizesCoOc90()));
    connect(matriz->getBt(2), SIGNAL(released()), this, SLOT(slotMatrizesCoOc45()));
    connect(matriz->getBt(3), SIGNAL(released()), this, SLOT(slotMatrizesCoOc0()));
    connect(matriz->getBt(5), SIGNAL(released()), this, SLOT(slotMatrizesCoOc0()));
    connect(matriz->getBt(6), SIGNAL(released()), this, SLOT(slotMatrizesCoOc45()));
    connect(matriz->getBt(7), SIGNAL(released()), this, SLOT(slotMatrizesCoOc90()));
    connect(matriz->getBt(8), SIGNAL(released()), this, SLOT(slotMatrizesCoOc135()));

}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Abrir"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Carregar uma nova imagem"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(slotOpen()));

    resultAct = new QAction(tr("&Exibir"), this);
    resultAct->setStatusTip(tr("Exibir resultados dos ATH calculados"));
    resultAct->setEnabled(false);
    connect(resultAct, SIGNAL(triggered()), this, SLOT(slotResult()));

    matrizAct = new QAction(tr("&Matriz"), this);
    matrizAct->setStatusTip(tr("Exibe as Matrizes de Co-ocorência"));
    matrizAct->setEnabled(false);
    connect(matrizAct, SIGNAL(triggered()), this, SLOT(slotMatriz()));    
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&Arquivo"));
    fileMenu->addAction(openAct);

    resultsMenu = menuBar()->addMenu(tr("&Resultados"));
    resultsMenu->addAction(resultAct);
    resultsMenu->addAction(matrizAct);
}

void MainWindow::createGUI()
{
    createPreview();
    createATH();
    createDMCO();
    createNT();
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
    //caixaDMCO->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    caixaDMCO->setKeyboardTracking(true);
    caixaDMCO->setMinimum(1);
    caixaDMCO->setMaximum(99999);
    caixaDMCO->setVisible(true);
}

void MainWindow::createNT()
{
    frameNT = new QFrame(this->centralWidget());
    frameNT->setEnabled(true);
    frameNT->setGeometry(680,141, 241,71);
    frameNT->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frameNT->setLineWidth(1);
    frameNT->setFrameShadow(QFrame::Raised);
    frameNT->setFrameShape(QFrame::StyledPanel);
    frameNT->setVisible(true);

    labelNT = new QLabel(frameNT);
    labelNT->setText("NUMERO DE THREADS");
    labelNT->setGeometry(50,0,161,16);
    labelNT->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    labelNT->setVisible(true);

    caixaNT = new QSpinBox(frameNT);
    caixaNT->setEnabled(true);
    caixaNT->setGeometry(40,30,160,30);
    caixaNT->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    //caixaNT->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    caixaNT->setKeyboardTracking(true);
    caixaNT->setMinimum(1);
    caixaNT->setMaximum(99999);
    caixaNT->setValue(4);
    caixaNT->setVisible(true);
}

/*
 *
 *
 *
 * SLOTS
 *
 *
 *
 */

void MainWindow::slotMatrizesCoOc0()
{
    matriz->exibeResults(ath->getMc0(), pow(2, openFile->getNc()), "Matriz 0º");
}

void MainWindow::slotMatrizesCoOc45()
{
    matriz->exibeResults(ath->getMc45(), pow(2, openFile->getNc()), "Matriz 45º");
}

void MainWindow::slotMatrizesCoOc90()
{
    matriz->exibeResults(ath->getMc90(), pow(2, openFile->getNc()), "Matriz 90º");
}

void MainWindow::slotMatrizesCoOc135()
{
    matriz->exibeResults(ath->getMc135(), pow(2, openFile->getNc()), "Matriz 135º");
}

void MainWindow::slotOpen()
{
    if(openFile == NULL)
        openFile = new GUIImageLoader();

    openFile->exec();
    loader = openFile->getLoader();
    areaPreview->setWidget(loader->getImgPreview());
    ui->extrairPb->setEnabled(true);
    frameATH->setEnabled(true);
    frameDMCO->setEnabled(true);
    frameNT->setEnabled(true);
    isNovaImg = true;

    for(int i = 1; i < 14; i++)
    {
        atributosSelecionados[i] = -2;
        boxCheckeds[i] = false;
        caixasDeSelecao[i]->setChecked(false);
        caixaDMCO->setValue(1);
        caixaNT->setValue(4);
    }
}

void MainWindow::slotResult()
{
    results->exec();
}

void MainWindow::slotMatriz()
{
    matriz->exec();
}

void MainWindow::slotExtracao()
{
    if(results == NULL)
        results = new GUIResults();
    results->limpaGUI();

    for(int i = 1; i < 14; i++)
        boxCheckeds[i] = caixasDeSelecao[i]->isChecked();

    if(loader->getStatus())
    {
        if(isNovaImg)
        {
            int NG = pow(2, openFile->getNc());
            matrizCoN_CPU = new double[NG * NG];
            ath = new Haralick(loader->getMatrizOrig(), openFile->getLargura(), openFile->getAltura(), NG, caixaNT->value());
            ath->calcularMatrizCoN(matrizCoN_CPU, caixaDMCO->value());
            ath->atCpu(matrizCoN_CPU, NG);

            isNovaImg = false;
        }
        ath->calcATH(atributosSelecionados, boxCheckeds);
    }

    results->setAtributos(atributosSelecionados, nomesATH, boxCheckeds);
    resultAct->setEnabled(true);
    matrizAct->setEnabled(true);

}

void MainWindow::slotSelectAll()
{
    if(caixasDeSelecao[0]->isChecked())
        for(int i = 1; i < 14; i++)
            caixasDeSelecao[i]->setChecked(true);
    else
        for(int i = 1; i < 14; i++)
            caixasDeSelecao[i]->setChecked(false);
}

void MainWindow::slotATHs()
{
    if(caixasDeSelecao[0]->isChecked())
        caixasDeSelecao[0]->setChecked(false);
}
