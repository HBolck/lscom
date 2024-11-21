#include "lscom.h"
#include "ui_lscom.h"

lscom::lscom(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lscom)
{
    ui->setupUi(this);

    //构建服务类对象
    this->log = new LogService();
    this->serial = new serialImp(log,this->ui->log_text);    

    initView();
    // log->setTextLog(this->ui->log_text,"启动初始化结束",Inner,Info);
}

/**
 * @brief 初始化页面
 */
void lscom::initView()
{
    //设置日志区域不可编辑
    ui->log_text->setReadOnly(true);
    //设置按钮组可用状态（后续抽出来，更改为状态机之类的机制控制）
    this->ui->btu_open_com->setEnabled(true);
    this->ui->btu_close_com->setEnabled(false);
    this->ui->btu_send_data->setEnabled(false);
    //初始化串口参数
    ui->comPortBox->clear();
    ui->comPortBox->addItems(serial->getSerialPorts());
    ui->comboBox_BaudRate->addItems(serial->getSerialBundRates());
    ui->comboBox_BaudRate->setCurrentIndex(3);//9600
    ui->comboBox_DateBits->addItems(serial->getSerialDataBits());
    ui->comboBox_DateBits->setCurrentIndex(3);//8
    ui->comboBox_StopBits->addItems(serial->getSerialStopBits());
    ui->comboBox_Parity->addItems(serial->getSerialParity());
}


/**
 * @brief 开启串口
 */
void lscom::on_btu_open_com_clicked()
{
    SerialPortConfig config;
    config.Baudrate = serial->mathBaudRate(this->ui->comboBox_BaudRate->currentText());
    config.DataBits = serial->mathDataBits(this->ui->comboBox_DateBits->currentText());
    config.StopBits = serial->mathStopBits(this->ui->comboBox_StopBits->currentText());
    config.Parity = serial->mathParity(this->ui->comboBox_Parity->currentText());
    config.PortName = this->ui->comPortBox->currentText();
    this->serial->initSerialPortInstance(config);
    this->serial->openPort();
    if(this->serial->isConnected()){
        this->ui->btu_open_com->setEnabled(false);
        this->ui->btu_send_data->setEnabled(true);
        this->ui->btu_close_com->setEnabled(true);
    }
}

/**
 * @brief 关闭串口
 */
void lscom::on_btu_close_com_clicked()
{
    this->serial->closePort();
    this->ui->btu_open_com->setEnabled(true);
    this->ui->btu_send_data->setEnabled(false);
    this->ui->btu_close_com->setEnabled(false);
}

/**
 * @brief 发送数据
 */
void lscom::on_btu_send_data_clicked()
{
    auto data = this->ui->text_send->toPlainText();
    this->log->setTextLog(this->ui->log_text,data.toUtf8().constData(),Send,Info);
    this->serial->sendData(data.toUtf8());
}

/**
 * @brief 清空窗口
 */
void lscom::on_btu_clear_log_text_clicked()
{
    this->ui->log_text->clear();
}

/**
 * @brief hex显示勾选事件
 * @param checked
 */
void lscom::on_cb_hex_display_clicked(bool checked)
{
    this->serial->setIsHexDisplay(checked);
}
/**
 * @brief hex发送勾选事件
 * @param checked
 */
void lscom::on_cb_hex_send_clicked(bool checked)
{
    this->serial->setIsHexSend(checked);
}

lscom::~lscom()
{
    delete serial;
    delete log;
    delete ui;
}











