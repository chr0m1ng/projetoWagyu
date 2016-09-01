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
    btMatriz = new QPushButton*[9];
    createButtons();
}

GUIMatrizCoo::~GUIMatrizCoo()
{
    delete txtMat;
    delete ui;
}

void GUIMatrizCoo::createButtons()
{
    QString caminho;
    int left = 0, top = 0;
    for(int i = 0; i < 9; i++)
    {
        caminho = QDir::currentPath() + "/../projetoWagyu/Extras/Matriz_0" + QString::number(i+1) + ".png";
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

QPushButton * GUIMatrizCoo::getBt(int i)
{
    return btMatriz[i];
}

void GUIMatrizCoo::exibeResults(unsigned short *matrizCoOc, int N, QString mat)
{
    this->hide();
    this->matrizCoOc = matrizCoOc;
    this->N = N;
    this->mat = mat;

    QDesktopWidget t;
    QRect screenSize = t.availableGeometry(t.primaryScreen());
    QWidget* wgMat = new QWidget;
    txtMat = new QPlainTextEdit(wgMat);

    wgMat->resize(screenSize.width(), screenSize.height());
    txtMat->resize(screenSize.width(), screenSize.height() - 100);
    txtMat->setReadOnly(true);
    wgMat->setWindowTitle(mat);
    QPushButton* btSalvar = new QPushButton("Salvar", wgMat);
    QPushButton* btFechar = new QPushButton("Fechar", wgMat);
    btFechar->setGeometry(screenSize.width() - 150, screenSize.height() - 95, 100, 40);
    btSalvar->setGeometry(screenSize.width() - 280, screenSize.height() - 95, 100, 40);


    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            QString tmp = QString::number(matrizCoOc[i]) + " ";
            txtMat->insertPlainText(tmp);

        }
        txtMat->appendPlainText("");
    }

    connect(btSalvar, SIGNAL(released()), this, SLOT(slotSalvarArquivo()));
    connect(btFechar, SIGNAL(released()), wgMat, SLOT(close()));

    wgMat->show();
}

void GUIMatrizCoo::slotSalvarArquivo()
{
    QString caminho = QFileDialog::getSaveFileName(this, "Salvar Arquivo", QDir::currentPath());

    if(!caminho.isEmpty())
    {
        caminho.append(".txt");
        QFile file(caminho);
        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << mat + "\n\n";
            stream << txtMat->toPlainText();
            file.flush();
            file.close();
            QMessageBox::information(this, tr("Salvo"),tr("Salvo com sucesso em %1.").arg(caminho));
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), tr("Impossivel salvar arquivo"));
            return;
        }
    }
}
