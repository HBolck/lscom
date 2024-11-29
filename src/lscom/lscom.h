#ifndef LSCOM_H
#define LSCOM_H

#include <QMainWindow>
#include "Service/serviceadapter.h"
#include <QTimer>
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>
#include "Delegate/qstylewithbuttondelegate.h"

#endif // LSCOM_H



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


private slots:

    void onPortDataReved(long data);

    void onPortDataSend(long data);

    void on_btu_open_com_clicked();

    void on_btu_close_com_clicked();

    void on_btu_send_data_clicked();

    void on_btu_clear_log_text_clicked();

    void on_cb_hex_display_clicked(bool checked);

    void on_cb_hex_send_clicked(bool checked);

    void on_btu_clear_send_text_clicked();

    void on_cb_time_send_clicked(bool checked);

    void on_btu_set_param_clicked();

    void on_cB_rev_to_file_clicked(bool checked);

private:
    Ui::lscom *ui;
    // lscom_service::serialImp *serial;
    // lscom_service::LogService *log;
    lscom_service::ServiceAdapter *serviceAdapter;

    QTimer* sendDataTimer;
    bool _sendTimerStart = false;

    /**
     * @brief 接收计数，发送计数
     */
    long recConter,sendConter;

    /**
     * @brief 版本
     */
    QLabel *version;

    /**
     * @brief 源码链接
     */
    QLabel *sourceCodelinkLable;

    /**
     * @brief 接收计数标签
     */
    QLabel *recConterLabel;
    /**
     * @brief 发送计数标签
     */
    QLabel *sendConterLabel;

    /**
     * @brief 初始化页面
     */
    void initView();
    /**
     * @brief 初始化定时器
     */
    void initTimer();

    /**
     * @brief 销毁定时器
     */
    void distoryTimer();

    /**
     * @brief 初始化状态栏
     */
    void initStatusBar();

    /**
     * @brief 初始化数据表格
     */
    void initTalbeView(Config &config);
};

