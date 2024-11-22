#include "lscom.h"
#include "ui_lscom.h"

lscom::lscom(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::lscom)
{
    ui->setupUi(this);

    // 构建服务类对象
    this->log = new LogService();
    this->serial = new serialImp(log, this->ui->log_text);
    initView();

    // this->serial->updateRevCountPrt() = &lscom::updateRevConter;
}

/**
 * @brief 初始化页面
 */
void lscom::initView()
{

    initStatusBar();

    // 设置默认发送时间间隔
    this->ui->sendperiod->setText("1000");
    // 设置日志区域不可编辑
    ui->log_text->setReadOnly(true);
    // 设置按钮组可用状态（后续抽出来，更改为状态机之类的机制控制）
    this->ui->btu_open_com->setEnabled(true);
    this->ui->btu_close_com->setEnabled(false);
    this->ui->btu_send_data->setEnabled(false);
    // 初始化串口参数
    ui->comPortBox->clear();
    ui->comPortBox->addItems(serial->getSerialPorts());
    ui->comboBox_BaudRate->addItems(serial->getSerialBundRates());
    ui->comboBox_BaudRate->setCurrentIndex(3); // 9600
    ui->comboBox_DateBits->addItems(serial->getSerialDataBits());
    ui->comboBox_DateBits->setCurrentIndex(3); // 8
    ui->comboBox_StopBits->addItems(serial->getSerialStopBits());
    ui->comboBox_Parity->addItems(serial->getSerialParity());
}

/**
 * @brief lscom::初始化状态栏
 */
void lscom::initStatusBar()
{
    // 源码链接描述
    sourceCodelinkLable = new QLabel(this);
    sourceCodelinkLable->setOpenExternalLinks(true);
    sourceCodelinkLable->setText("<style> a {text-decoration: none} </style> <a href=\"https://gitee.com/hblockd/lscom\">源代码");
    sourceCodelinkLable->setMinimumSize(40, 20);

    this->ui->statusbar->addWidget(sourceCodelinkLable);
    this->version = new QLabel(this);
    this->version->setText("v1.2.0");
    version->setMinimumSize(40, 20);

    this->ui->statusbar->addWidget(version);
    this->recConterLabel = new QLabel(this);
    this->sendConterLabel = new QLabel(this);

    sendConterLabel->setMinimumSize(80, 20);
    recConterLabel->setMinimumSize(80, 20);
    version->setMinimumSize(40, 20);
    sourceCodelinkLable->setMinimumSize(40, 20);
    this->recConter = 0;
    this->sendConter = 0;
    setNumOnLabel(this->recConterLabel, "R:", recConter);
    setNumOnLabel(this->sendConterLabel, "S:", sendConter);
    this->ui->statusbar->addWidget(recConterLabel);
    this->ui->statusbar->addWidget(sendConterLabel);
}

/**
 * @brief 初始化定时器
 */
void lscom::initTimer()
{
    // distoryTimer();
    QString sendperiodTime = this->ui->sendperiod->text();
    if (sendperiodTime.isEmpty())
    {
        this->log->setTextLog(this->ui->log_text, "时间间隔不能为空！", Inner, Error);
        return;
    }
    uint interval;
    bool flag = isQStringToUint(sendperiodTime, &interval);
    if (!flag)
    {
        this->log->setTextLog(this->ui->log_text, "时间间隔格式错误！", Inner, Error);
        return;
    }
    this->sendDataTimer = new QTimer();
    this->sendDataTimer->setInterval(interval);
    // 注册发送命令 定义槽关联
    connect(this->sendDataTimer, &QTimer::timeout, this, &lscom::on_btu_send_data_clicked);
    // 开启定时器
    this->sendDataTimer->start();
    this->_sendTimerStart = true;
    // 设置发送按钮不可用
    this->ui->btu_send_data->setEnabled(false);
}

/**
 * @brief 销毁定时器
 */
void lscom::distoryTimer()
{
    if (this->sendDataTimer != nullptr)
    {
        if (this->_sendTimerStart)
        {
            this->sendDataTimer->stop();
            this->_sendTimerStart = false;
            // 解绑定时器关联的槽事件
            disconnect(this->sendDataTimer, &QTimer::timeout, this, &lscom::on_btu_send_data_clicked);
            // todo:这个地方保持怀疑态度，可能会出现内存泄露的情况
            delete this->sendDataTimer;
            // 恢复发送按钮可用状态
            this->ui->btu_send_data->setEnabled(true);
        }
    }
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
    if (this->serial->isConnected())
    {
        this->ui->btu_open_com->setEnabled(false);
        this->ui->btu_send_data->setEnabled(true);
        this->ui->btu_close_com->setEnabled(true);
        connect(this->serial, &serialImp::serialRevDataSignal, this, &lscom::oSerialReved);
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
    disconnect(this->serial, &serialImp::serialRevDataSignal, this, &lscom::oSerialReved);
}

/**
 * @brief 发送数据
 */
void lscom::on_btu_send_data_clicked()
{
    auto data = this->ui->text_send->toPlainText();
    if (data.isEmpty())
        return;
    this->log->setTextLog(this->ui->log_text, data.toUtf8().constData(), Send, Info);
    this->serial->sendData(data.toUtf8());
    setNumOnLabel(sendConterLabel, "S:", sendConter += data.toUtf8().size());
}

/**
 * @brief 清空窗口
 */
void lscom::on_btu_clear_log_text_clicked()
{
    this->ui->log_text->clear();
    recConter = 0;
    setNumOnLabel(recConterLabel, "R:", 0);
}

/**
 * @brief 清空发送区内容
 */
void lscom::on_btu_clear_send_text_clicked()
{
    this->ui->text_send->clear();
    sendConter = 0;
    setNumOnLabel(sendConterLabel, "S:", 0);
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

/**
 * @brief 定时发送勾选事件
 * @param checked
 */
void lscom::on_cb_time_send_clicked(bool checked)
{
    if (this->serial->isConnected())
    {
        if (checked)
        {
            this->initTimer();
        }
        else
        {
            this->distoryTimer();
        }
    }
}

lscom::~lscom()
{
    this->distoryTimer();
    delete serial;
    delete log;
    delete ui;
}

void lscom::oSerialReved(long data)
{
    setNumOnLabel(recConterLabel, "R:", recConter += data);
}
