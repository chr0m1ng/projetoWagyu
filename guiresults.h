#ifndef GUIRESULTS_H
#define GUIRESULTS_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class GUIResults;
}

class GUIResults : public QDialog
{
    Q_OBJECT

public:
    explicit GUIResults(QWidget *parent = 0);
    ~GUIResults();
    void setAtributos(double *&atributosSelecionados, QString*nomesATH);

private:
    Ui::GUIResults *ui;

    int nAtributos = 0;
    double *atributosSelecionados;
    QLabel *labelsAtributos[14];
    QString *nomesATH;
    void createLabels();
};

#endif // GUIRESULTS_H
