#include "guimatrizcoo.h"
#include "ui_guimatrizcoo.h"

GUIMatrizCoo::GUIMatrizCoo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIMatrizCoo)
{
    ui->setupUi(this);
    this->setFixedHeight(113*3);
    this->setFixedWidth(113*3);
    this->setWindowTitle("Matriz de Co-Ocorrência");
    createButtons();
}

GUIMatrizCoo::~GUIMatrizCoo()
{
    delete ui;
}

void GUIMatrizCoo::createButtons()
{
    QString caminho;
    int left = 0, top = 0;
    for(int i = 0; i < 9; i++)
    {
        caminho = QDir::currentPath() + "/Extras/Matriz_0" + QString::number(i+1) + ".png";
        QPixmap img(caminho);
        QIcon icon(img);
        btMatriz[i] = new QPushButton(this);
        btMatriz[i]->setGeometry(left, top, 113,113);
        btMatriz[i]->setIcon(icon);
        btMatriz[i]->setIconSize(img.rect().size());
        btMatriz[i]->setVisible(true);
        if((i+1)%3 == 0)
        {
            left = 0;
            top +=113;
        }
        else
            left += 113;
    }
}
