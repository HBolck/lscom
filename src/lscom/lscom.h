#ifndef LSCOM_H
#define LSCOM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class lscom;
}
QT_END_NAMESPACE

class lscom : public QMainWindow
{
    Q_OBJECT

public:
    lscom(QWidget *parent = nullptr);
    ~lscom();

private:
    Ui::lscom *ui;
};
#endif // LSCOM_H
