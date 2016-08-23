#include "guiresult.h"
#include "ui_guiresult.h"

GUIResult::GUIResult(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUIResult)
{
    ui->setupUi(this);
}

GUIResult::~GUIResult()
{
    delete ui;
}
