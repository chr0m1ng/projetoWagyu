#include "guiresults.h"
#include "ui_guiresults.h"

GUIResults::GUIResults(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIResults)
{
    ui->setupUi(this);
}

GUIResults::~GUIResults()
{
    delete ui;
}

void GUIResults::setAtributos(double *&atributosSelecionados, QString *nomesATH)
{
    this->atributosSelecionados = atributosSelecionados;
    this->nomesATH = nomesATH;

    createLabels();
}

void GUIResults::createLabels()
{
    int h = 20;

    for(int i = 1; i < 14; i++)
    {
        if(atributosSelecionados[i] != -2)
        {
            labelsAtributos[i] = new QLabel(nomesATH[i] + " = " + QString::number(atributosSelecionados[i]), this);
            labelsAtributos[i]->setGeometry(20,h,191,16);
            labelsAtributos[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            labelsAtributos[i]->setVisible(true);
            h += 20;
        }
    }
}
