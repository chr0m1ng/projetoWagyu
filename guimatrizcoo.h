#ifndef GUIMATRIZCOO_H
#define GUIMATRIZCOO_H

#include <QDialog>
#include <QPushButton>
#include <QDir>
#include <QImage>
#include <QLabel>
#include <QMessageBox>

namespace Ui {
class GUIMatrizCoo;
}

class GUIMatrizCoo : public QDialog
{
    Q_OBJECT

public:
    explicit GUIMatrizCoo(QWidget *parent = 0);
    ~GUIMatrizCoo();

private:
    Ui::GUIMatrizCoo *ui;
    QPushButton **btMatriz = new QPushButton*[9];
    void createButtons();
};

#endif // GUIMATRIZCOO_H
