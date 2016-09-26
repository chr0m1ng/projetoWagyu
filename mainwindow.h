#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QCheckBox>
#include <QSpinBox>
#include <QEventLoop>
#include <QMenu>
#include <cmath>
#include <QTime>
#include <QDirIterator>
#include "guimatrizcoo.h"
#include "guiresults.h"
#include "imgloader.h"
#include "haralick.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GUIResults *results = NULL;
    GUIMatrizCoo *matriz = NULL;
    ImgLoader *loader = NULL;
    double * matrizCoN_CPU;
    double * atributosSelecionados;
    QVector<QString> caminhoImg;

    void carregaCaminho();

    bool * boxCheckeds;

    // GUI
        // MenuBar
        void createActions();
        void createMenu();
        QMenu *fileMenu;
        QMenu *resultsMenu;
        QAction *openAct;
        QAction *resultAct;
        QAction *matrizAct;
        Haralick *ath;

        // GuiPrincipal
        void createConnections();
        void createGUI();
        void createPreview();
        void createATH();
        void createDMCO();
        void createNT();
        QFrame *framePreview;
        QFrame *frameATH;
        QFrame *frameDMCO;
        QFrame *frameNT;
        QLabel *labelPreview;
        QLabel *labelATH;
        QLabel *labelDMCO;
        QLabel *labelNT;
        QScrollArea *areaPreview;
        QSpinBox *caixaDMCO;
        QSpinBox *caixaNT;
        //CheckBox
        QString nomesATH[14];
        QCheckBox **caixasDeSelecao;
        void createBoxes();

private slots:
    void slotOpen();
    void slotResult();
    void slotMatriz();
    void slotExtracao();
    void slotMatrizesCoOc0();
    void slotMatrizesCoOc45();
    void slotMatrizesCoOc90();
    void slotMatrizesCoOc135();
    void slotMatrizesCoOc();

    //Slots CheckBox
    void slotSelectAll();
    void slotATHs();

};

#endif // MAINWINDOW_H
