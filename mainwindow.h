#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
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
    ImgLoader *loader;


private:
    Ui::MainWindow *ui;
    int largura;
    int altura;
    int nc;
private slots:
    void slotCarregarPress();

};

#endif // MAINWINDOW_H
