#ifndef GUIRESULTS_H
#define GUIRESULTS_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>

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

    QFrame *frameATH;
    QLabel *labelsAtributos[14];
    QLineEdit *lineValue[14];
    QString *nomesATH;
    double *atributosSelecionados;

    QPushButton *salvar;
    QPushButton *fechar;

    void createLabels();
    void createFrame();
};

#endif // GUIRESULTS_H
