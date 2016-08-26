#include "guiresults.h"
#include "ui_guiresults.h"

GUIResults::GUIResults(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIResults)
{
    ui->setupUi(this);
    this->setWindowTitle("Resultados");
    this->setGeometry(0,0,480,370);
}

GUIResults::~GUIResults()
{
    delete frameATH;
    delete atributosSelecionados;
    delete[] lineValue;
    delete[] labelsAtributos;
    delete nomesATH;
    delete ui;
}

void GUIResults::setAtributos(double *&atributosSelecionados, QString *nomesATH)
{
    this->atributosSelecionados = atributosSelecionados;
    this->nomesATH = nomesATH;

    createFrame();
    createLabels();

    salvar = new QPushButton("Salvar...", this);
    salvar->setEnabled(true);
    salvar->setGeometry(360,20,100,50);
    salvar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    salvar->setVisible(true);

    fechar = new QPushButton("Fechar", this);
    fechar->setEnabled(true);
    fechar->setGeometry(360,90,100,50);
    fechar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    fechar->setVisible(true);
}

void GUIResults::createFrame()
{
    frameATH = new QFrame(this);
    frameATH->setEnabled(true);
    frameATH->setGeometry(20,20,320,330);
    frameATH->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    frameATH->setLineWidth(1);
    frameATH->setFrameShadow(QFrame::Raised);
    frameATH->setFrameShape(QFrame::StyledPanel);
    frameATH->setVisible(true);
}

void GUIResults::createLabels()
{
    int h = 20;

    for(int i = 1; i < 14; i++)
    {
        if(atributosSelecionados[i] != -2)
        {
            lineValue[i] = new QLineEdit(QString::number(atributosSelecionados[i]), this->frameATH);
            lineValue[i]->setGeometry(200,h,100,16);
            lineValue[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            lineValue[i]->setReadOnly(true);
            lineValue[i]->setVisible(true);

            labelsAtributos[i] = new QLabel(nomesATH[i] + " = ", this->frameATH);
            labelsAtributos[i]->setGeometry(20,h,191,16);
            labelsAtributos[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            labelsAtributos[i]->setVisible(true);
            h += 20;
        }
    }
}
