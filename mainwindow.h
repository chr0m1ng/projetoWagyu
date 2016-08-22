#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QCheckBox>
#include <QMenu>
#include <QSpinBox>
#include <cmath>
#include "guiloadimage.h"
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

    double * matrizCoN_CPU;

    void conexoes();
    GUILoadImage *openFile;
    ImgLoader *loader = NULL;
    bool atributos[13];

    // GUI
        // MenuBar
        void createActions();
        void createMenus();
        QMenu *fileMenu;
        QAction *openAct;
        Haralick *ath;

        // GuiPrincipal
        void createGUI();
        void createPreview();
        void createATH();
        void createDMCO();
        QFrame *framePreview;
        QFrame *frameATH;
        QFrame *frameDMCO;
        QLabel *labelPreview;
        QLabel *labelATH;
        QLabel *labelDMCO;
        QScrollArea *areaPreview;
        QSpinBox *caixaDMCO;
        //CheckBox
        QString nomesATH[14] = {"Selecionar Todos", "Energia",
                               "Contraste", "Correlação",
                               "Variancia", "MDI",
                               "Media Soma", "Variancia Soma",
                               "Entropia Soma", "Entropia",
                               "Variancia Diferença", "Entropia Diferença",
                               "Medidas Correlação 1", "Medidas Correlação 2"};
        QCheckBox *caixasDeSelecao[14];
        void createBoxes();

private slots:
    void slotOpen();
    void slotExtracao();

    //Slots CheckBox
    void slotSel();
    void slotATH();

};

#endif // MAINWINDOW_H
