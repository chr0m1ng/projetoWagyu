#include "guiresults.h"
#include "ui_guiresults.h"

GUIResults::GUIResults(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIResults)
{
    ui->setupUi(this);
    this->setWindowTitle("Resultados");
}

GUIResults::~GUIResults()
{
    delete frameATH;
    delete atributosSelecionados;
    delete[] lineValue;
    delete[] labelsAtributos;
    delete nomesATH;
    delete salvar;
    delete fechar;
    delete ui;
}

void GUIResults::setAtributos(double *&atributosSelecionados, QString *nomesATH)
{
    this->atributosSelecionados = atributosSelecionados;
    this->nomesATH = nomesATH;

    createFrame();
    createLabels();
}


void GUIResults::limpaGUI()
{
    for(int i = 1; i < 14; i++)
    {
        if(labelsAtributos[i] != NULL)
        {
            delete labelsAtributos[i];
            delete lineValue[i];
            labelsAtributos[i] = NULL;
            lineValue[i] = NULL;
        }
    }
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

    salvar = new QPushButton("Salvar...", this);
    salvar->setEnabled(true);
    salvar->setGeometry(360,20,100,50);
    salvar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    salvar->setVisible(true);
    connect(salvar, SIGNAL(released()), this, SLOT(slotSalvarArquivo()));

    fechar = new QPushButton("Fechar", this);
    fechar->setEnabled(true);
    fechar->setGeometry(360,90,100,50);
    fechar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    fechar->setVisible(true);
    connect(fechar, SIGNAL(released()), this, SLOT(close()));
}

void GUIResults::createLabels()
{
    int h = 20;

    for(int i = 1; i < 14; i++)
    {
        if(atributosSelecionados[i] != -2)
        {
            labelsAtributos[i] = new QLabel(nomesATH[i] + " = ", this->frameATH);
            labelsAtributos[i]->setGeometry(20,h,191,16);
            labelsAtributos[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            labelsAtributos[i]->setVisible(true);

            lineValue[i] = new QLineEdit(QString::number(atributosSelecionados[i]), this->frameATH);
            lineValue[i]->setGeometry(200,h,100,16);
            lineValue[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            lineValue[i]->setReadOnly(true);
            lineValue[i]->setVisible(true);

            h += 20;
        }
    }
}

void GUIResults::slotSalvarArquivo()
{
    caminho = QFileDialog::getSaveFileName(this, "Salvar Arquivo", QDir::currentPath());

    if(!caminho.isEmpty())
    {
        caminho.append(".txt");
        QByteArray ba = caminho.toLatin1();
        const char *c_str = ba.data();

        FILE *athResults = fopen(c_str, "w");
        fprintf(athResults, "RESULTADO\n\n");
        for(int i = 1; i < 14; i++)
            if(atributosSelecionados[i] != -2)
            {
                ba = nomesATH[i].toLatin1();
                const char *n_str = ba.data();

                ba = QString::number(atributosSelecionados[i]).toLatin1();
                const char *nm_str = ba.data();

                fprintf(athResults, "%s = %s\n", n_str, nm_str);
            }
        fclose(athResults);
    }
}

