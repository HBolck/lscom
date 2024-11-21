#ifndef LSCOM_H
#define LSCOM_H

#include <QMainWindow>
#include "Service/serial_imp.h"
#include "Service/logservice.h"

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
    void initView();
    ~lscom();

private slots:
    void on_btu_open_com_clicked();
    void on_btu_close_com_clicked();

    void on_btu_send_data_clicked();

private:
    Ui::lscom *ui;
    serialImp *serial;
    LogService *log;
};
#endif // LSCOM_H
