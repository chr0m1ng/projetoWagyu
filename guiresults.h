#ifndef GUIRESULTS_H
#define GUIRESULTS_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>

namespace Ui {
class GUIResults;
}

class GUIResults : public QDialog
{
    Q_OBJECT

public:
    explicit GUIResults(QWidget *parent = 0);
    ~GUIResults();
    void setAtributos(double *&atributosSelecionados, QString*nomesATH, bool * boxCheckeds);

private:
    Ui::GUIResults *ui;

    QPlainTextEdit *frameATH;
    QString *nomesATH;
    double *atributosSelecionados;
    bool *boxCheckeds;

    QString caminho;
    QPushButton *salvar;
    QPushButton *fechar;

    void createLabels();
    void createFrame();

private slots:
    void slotSalvarArquivo();
};

#endif // GUIRESULTS_H
