#ifndef GUIMATRIZCOO_H
#define GUIMATRIZCOO_H

#include <QDialog>
#include <QPushButton>
#include <QDir>
#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QTextStream>



namespace Ui {
class GUIMatrizCoo;
}

class GUIMatrizCoo : public QDialog
{
    Q_OBJECT

public:
    explicit GUIMatrizCoo(QWidget *parent = 0);
    ~GUIMatrizCoo();
    QPushButton * getBt(int i);
    void exibeResults(unsigned short *matrizCoOc, int N, QString mat);

private:
    Ui::GUIMatrizCoo *ui;
    QPushButton **btMatriz;
    void createButtons();
    unsigned short *matrizCoOc;
    int N;
    QPlainTextEdit* txtMat;
    QString mat;
private slots:
    void slotSalvarArquivo();
};

#endif // GUIMATRIZCOO_H
