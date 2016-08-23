#ifndef GUIRESULT_H
#define GUIRESULT_H

#include <QMainWindow>

namespace Ui {
class GUIResult;
}

class GUIResult : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUIResult(QWidget *parent = 0);
    ~GUIResult();

private:
    Ui::GUIResult *ui;
};

#endif // GUIRESULT_H
