#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenu>
#include <QVBoxLayout>
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

    // MenuBar
    void createActions();
    void createMenus();
    QMenu *fileMenu;
    QAction *openAct;
    Haralick *ath;

private slots:
    void slotOpen();
    void slotExtracao();

    //Slots CheckBox
    void slotSel();
    void slotATH01();
    void slotATH02();
    void slotATH03();
    void slotATH04();
    void slotATH05();
    void slotATH06();
    void slotATH07();
    void slotATH08();
    void slotATH09();
    void slotATH10();
    void slotATH11();
    void slotATH12();
    void slotATH13();

};

#endif // MAINWINDOW_H
