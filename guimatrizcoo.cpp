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

void GUIMatrizCoo::exibeResults(int *matrizCoOc, int N, QString mat)
{
    this->hide();
    this->matrizCoOc = matrizCoOc;
    this->N = N;
    this->mat = mat;

    QDesktopWidget t;
    QRect screenSize = t.availableGeometry(t.primaryScreen());
    QWidget* wgMat = new QWidget;
    wgMat->setWindowTitle(mat);

    QPushButton* btSalvar = new QPushButton("Salvar", wgMat);
    QPushButton* btFechar = new QPushButton("Fechar", wgMat);

    wgMat->resize(380, 405);
    wgMat->move(screenSize.width()/2 - wgMat->size().width()/2, screenSize.height()/2 - wgMat->size().height()/2);

    btSalvar->move(wgMat->size().width() / 2 - btSalvar->size().width() - 40, wgMat->size().height() - btSalvar->size().height() - 5);
    btFechar->move(wgMat->size().width() / 2 + 40, wgMat->size().height() - btFechar->size().height() - 5);
    btSalvar->resize(wgMat->size().width()/4, 40);
    btFechar->resize(wgMat->size().width()/4, 40);
    wgMat->setMinimumSize(wgMat->size());
    wgMat->setMaximumSize(wgMat->size());

    QPixmap pix("../projetoWagyu/Extras/gifinho.gif");
    if(pix.isNull())
    {
        pix = QPixmap(300, 300);
        pix.fill(Qt::red);
    }

    QSplashScreen *spl = new QSplashScreen(pix);
    spl->showMessage("Abrindo...", Qt::AlignCenter, Qt::black);
    qApp->processEvents(QEventLoop::AllEvents);
    spl->show();
    spl->raise();
    spl->activateWindow();

    QTime dieTime = QTime::currentTime().addMSecs(500);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    if(mat == "Matriz Total")
    {

        //Salva vetor extraido da imagem .raw em um .txt como se fosse um .pgm
        FILE *cam = fopen("matTot.txt", "w");
        if(cam == NULL)
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar arquivo"));
        }
        fprintf(cam, "P2\n%d %d\n%d\n", N, N, 255);
        int tam = N * N;
        for(int i = 0; i < tam; i++)
            fprintf(cam, "%d\n", matrizCoOc[i]);
        fclose(cam);
        QFile::rename("matTot.txt", "matTot.pgm");

        QImage img("matTot.pgm", "PGM");
        this->matTot = img.copy();
        this->matAtual = &this->matTot;

        QLabel *imgPreview = new QLabel;
        imgPreview->setBackgroundRole(QPalette::Base);
        imgPreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imgPreview->setScaledContents(true);

        QFrame *framePreview = new QFrame(wgMat);
        framePreview->setEnabled(true);
        framePreview->setGeometry(20,20,331,331);
        framePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        framePreview->setLineWidth(1);
        framePreview->setFrameShadow(QFrame::Raised);
        framePreview->setFrameShape(QFrame::StyledPanel);
        framePreview->setVisible(true);

        QLabel *labelPreview = new QLabel(framePreview);
        labelPreview->setText("PREVIEW");
        labelPreview->setGeometry(140,0,71,16);
        labelPreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        labelPreview->setVisible(true);

        QScrollArea *areaPreview = new QScrollArea(framePreview);
        areaPreview->setGeometry(10,20,311,301);
        areaPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        areaPreview->setFrameShadow(QFrame::Sunken);
        areaPreview->setFrameShape(QFrame::StyledPanel);
        areaPreview->setWidgetResizable(true);

        imgPreview->setPixmap(QPixmap::fromImage(img));
        imgPreview->adjustSize();

        areaPreview->setWidget(imgPreview);

        QFile::remove("matTot.pgm");

    }

    else if(mat == "Matriz 0º")
    {

        //Salva vetor extraido da imagem .raw em um .txt como se fosse um .pgm
        FILE *cam = fopen("mat0.txt", "w");
        if(cam == NULL)
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar arquivo"));
        }
        fprintf(cam, "P2\n%d %d\n%d\n", N, N, 255);
        int tam = N * N;
        for(int i = 0; i < tam; i++)
            fprintf(cam, "%d\n", matrizCoOc[i]);
        fclose(cam);
        QFile::rename("mat0.txt", "mat0.pgm");

        QImage img("mat0.pgm", "PGM");
        this->mat0 = img.copy();
        this->matAtual = &this->mat0;

        QLabel *imgPreview = new QLabel;
        imgPreview->setBackgroundRole(QPalette::Base);
        imgPreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imgPreview->setScaledContents(true);

        QFrame *framePreview = new QFrame(wgMat);
        framePreview->setEnabled(true);
        framePreview->setGeometry(20,20,331,331);
        framePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        framePreview->setLineWidth(1);
        framePreview->setFrameShadow(QFrame::Raised);
        framePreview->setFrameShape(QFrame::StyledPanel);
        framePreview->setVisible(true);

        QLabel *labelPreview = new QLabel(framePreview);
        labelPreview->setText("PREVIEW");
        labelPreview->setGeometry(140,0,71,16);
        labelPreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        labelPreview->setVisible(true);

        QScrollArea *areaPreview = new QScrollArea(framePreview);
        areaPreview->setGeometry(10,20,311,301);
        areaPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        areaPreview->setFrameShadow(QFrame::Sunken);
        areaPreview->setFrameShape(QFrame::StyledPanel);
        areaPreview->setWidgetResizable(true);

        imgPreview->setPixmap(QPixmap::fromImage(img));
        imgPreview->adjustSize();

        areaPreview->setWidget(imgPreview);

        QFile::remove("mat0.pgm");

    }

    else if(mat == "Matriz 45º")
    {

        //Salva vetor extraido da imagem .raw em um .txt como se fosse um .pgm
        FILE *cam = fopen("mat45.txt", "w");
        if(cam == NULL)
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar arquivo"));
        }
        fprintf(cam, "P2\n%d %d\n%d\n", N, N, 255);
        int tam = N * N;
        for(int i = 0; i < tam; i++)
            fprintf(cam, "%d\n", matrizCoOc[i]);
        fclose(cam);
        QFile::rename("mat45.txt", "mat45.pgm");

        QImage img("mat45.pgm", "PGM");
        this->mat45 = img.copy();
        this->matAtual = &this->mat45;


        QLabel *imgPreview = new QLabel;
        imgPreview->setBackgroundRole(QPalette::Base);
        imgPreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imgPreview->setScaledContents(true);

        QFrame *framePreview = new QFrame(wgMat);
        framePreview->setEnabled(true);
        framePreview->setGeometry(20,20,331,331);
        framePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        framePreview->setLineWidth(1);
        framePreview->setFrameShadow(QFrame::Raised);
        framePreview->setFrameShape(QFrame::StyledPanel);
        framePreview->setVisible(true);

        QLabel *labelPreview = new QLabel(framePreview);
        labelPreview->setText("PREVIEW");
        labelPreview->setGeometry(140,0,71,16);
        labelPreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        labelPreview->setVisible(true);

        QScrollArea *areaPreview = new QScrollArea(framePreview);
        areaPreview->setGeometry(10,20,311,301);
        areaPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        areaPreview->setFrameShadow(QFrame::Sunken);
        areaPreview->setFrameShape(QFrame::StyledPanel);
        areaPreview->setWidgetResizable(true);

        imgPreview->setPixmap(QPixmap::fromImage(img));
        imgPreview->adjustSize();

        areaPreview->setWidget(imgPreview);

        QFile::remove("mat45.pgm");

    }

    else if(mat == "Matriz 90º")
    {

        //Salva vetor extraido da imagem .raw em um .txt como se fosse um .pgm
        FILE *cam = fopen("mat90.txt", "w");
        if(cam == NULL)
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar arquivo"));
        }
        fprintf(cam, "P2\n%d %d\n%d\n", N, N, 255);
        int tam = N * N;
        for(int i = 0; i < tam; i++)
            fprintf(cam, "%d\n", matrizCoOc[i]);
        fclose(cam);
        QFile::rename("mat90.txt", "mat90.pgm");

        QImage img("mat90.pgm", "PGM");
        this->mat90 = img.copy();
        this->matAtual = &this->mat90;

        QLabel *imgPreview = new QLabel;
        imgPreview->setBackgroundRole(QPalette::Base);
        imgPreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imgPreview->setScaledContents(true);

        QFrame *framePreview = new QFrame(wgMat);
        framePreview->setEnabled(true);
        framePreview->setGeometry(20,20,331,331);
        framePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        framePreview->setLineWidth(1);
        framePreview->setFrameShadow(QFrame::Raised);
        framePreview->setFrameShape(QFrame::StyledPanel);
        framePreview->setVisible(true);

        QLabel *labelPreview = new QLabel(framePreview);
        labelPreview->setText("PREVIEW");
        labelPreview->setGeometry(140,0,71,16);
        labelPreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        labelPreview->setVisible(true);

        QScrollArea *areaPreview = new QScrollArea(framePreview);
        areaPreview->setGeometry(10,20,311,301);
        areaPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        areaPreview->setFrameShadow(QFrame::Sunken);
        areaPreview->setFrameShape(QFrame::StyledPanel);
        areaPreview->setWidgetResizable(true);

        imgPreview->setPixmap(QPixmap::fromImage(img));
        imgPreview->adjustSize();

        areaPreview->setWidget(imgPreview);

        QFile::remove("mat90.pgm");

    }

    else if(mat == "Matriz 135º")
    {

        //Salva vetor extraido da imagem .raw em um .txt como se fosse um .pgm
        FILE *cam = fopen("mat135.txt", "w");
        if(cam == NULL)
        {
            QMessageBox::information(this, tr("Image Viewer"),tr("Nao foi possivel carregar arquivo"));
        }
        fprintf(cam, "P2\n%d %d\n%d\n", N, N, 255);
        int tam = N * N;
        for(int i = 0; i < tam; i++)
            fprintf(cam, "%d\n", matrizCoOc[i]);
        fclose(cam);
        QFile::rename("mat135.txt", "mat135.pgm");

        QImage img("mat135.pgm", "PGM");
        this->mat135 = img.copy();
        this->matAtual = &this->mat135;

        QLabel *imgPreview = new QLabel;
        imgPreview->setBackgroundRole(QPalette::Base);
        imgPreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imgPreview->setScaledContents(true);

        QFrame *framePreview = new QFrame(wgMat);
        framePreview->setEnabled(true);
        framePreview->setGeometry(20,20,331,331);
        framePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        framePreview->setLineWidth(1);
        framePreview->setFrameShadow(QFrame::Raised);
        framePreview->setFrameShape(QFrame::StyledPanel);
        framePreview->setVisible(true);

        QLabel *labelPreview = new QLabel(framePreview);
        labelPreview->setText("PREVIEW");
        labelPreview->setGeometry(140,0,71,16);
        labelPreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        labelPreview->setVisible(true);

        QScrollArea *areaPreview = new QScrollArea(framePreview);
        areaPreview->setGeometry(10,20,311,301);
        areaPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        areaPreview->setFrameShadow(QFrame::Sunken);
        areaPreview->setFrameShape(QFrame::StyledPanel);
        areaPreview->setWidgetResizable(true);

        imgPreview->setPixmap(QPixmap::fromImage(img));
        imgPreview->adjustSize();

        areaPreview->setWidget(imgPreview);

        QFile::remove("mat135.pgm");

    }

    spl->finish(this);
    connect(btSalvar, SIGNAL(released()), this, SLOT(slotSalvarArquivo()));
    connect(btFechar, SIGNAL(released()), wgMat, SLOT(close()));

    wgMat->show();
}

void GUIMatrizCoo::slotSalvarArquivo()
{
    QString caminho = QFileDialog::getSaveFileName(this, "Salvar Arquivo", QDir::currentPath());
    if(!caminho.isEmpty())
        matAtual->save(caminho, "png");
}
