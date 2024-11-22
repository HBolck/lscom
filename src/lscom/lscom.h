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

    void on_btu_clear_log_text_clicked();

    void on_cb_hex_display_clicked(bool checked);

    void on_cb_hex_send_clicked(bool checked);

    void on_btu_clear_send_text_clicked();

private:
    Ui::lscom *ui;
    serialImp *serial;
    LogService *log;
};
#endif // LSCOM_H
