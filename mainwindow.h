#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenu>
#include <QVBoxLayout>
#include "guiloadimage.h"
#include "imgloader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void conexoes();
    GUILoadImage *openFile;
    ImgLoader *loader = NULL;


private:
    Ui::MainWindow *ui;
    int largura;
    int altura;
    int nc;

    // MenuBar
    void createActions();
    void createMenus();
    QMenu *fileMenu;
    QAction *openAct;

private slots:
    void slotOpen();

};

#endif // MAINWINDOW_H
