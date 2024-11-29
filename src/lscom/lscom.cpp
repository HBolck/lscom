#include "lscom.h"
#include "ui_lscom.h"

lscom::lscom(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::lscom)
{
    ui->setupUi(this);
    // 构建服务类对象
    this->serviceAdapter = new lscom_service::ServiceAdapter(this->ui->log_text);
    initView();
    Config config = this->serviceAdapter->configService->InitConfigFile();
    this->ui->sendperiod->setText(config.InputParam.SendInterval);
    this->ui->text_send->setText(config.InputParam.SendAreaData);
    //初始化表格数据内容
    initTalbeView(config);    
}

/**
 * @brief 初始化页面
 */
void lscom::initView()
{
    this->window()->setWindowTitle(GLOBAL_TITLE);
    initStatusBar();    
    // 设置日志区域不可编辑
    ui->log_text->setReadOnly(true);
    // 设置按钮组可用状态（后续抽出来，更改为状态机之类的机制控制）
    this->ui->btu_open_com->setEnabled(true);
    this->ui->btu_close_com->setEnabled(false);
    this->ui->btu_send_data->setEnabled(false);
    // 初始化串口参数
    ui->comPortBox->clear();
    ui->comPortBox->addItems(this->serviceAdapter->serialService->getSerialPorts());
    ui->comboBox_BaudRate->addItems(this->serviceAdapter->serialService->getSerialBundRates());
    ui->comboBox_BaudRate->setCurrentIndex(3); // 9600
    ui->comboBox_DateBits->addItems(this->serviceAdapter->serialService->getSerialDataBits());
    ui->comboBox_DateBits->setCurrentIndex(3); // 8
    ui->comboBox_StopBits->addItems(this->serviceAdapter->serialService->getSerialStopBits());
    ui->comboBox_Parity->addItems(this->serviceAdapter->serialService->getSerialParity());   
}

/**
 * @brief lscom::初始化状态栏
 */
void lscom::initStatusBar()
{
    // 源码链接描述
    sourceCodelinkLable = new QLabel(this);
    sourceCodelinkLable->setOpenExternalLinks(true);
    QString link = "<style> a {text-decoration: none} </style> <a href=";
    link.append(GLOBAL_CODE_SOURCE_URL);
    link.append(">源代码");
    sourceCodelinkLable->setText(link);
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
 * @brief 初始化数据表格
 */
void lscom::initTalbeView(Config &config)
{
    // 创建 QStandardItemModel 对象来存储数据
    QStandardItemModel *model = new QStandardItemModel;
    // 设置表头
    model->setHorizontalHeaderLabels(QStringList() << "数据" << "操作");
    // 向模型中添加数据
    for (int i = 0; i < config.InputParam.SendDataList.count(); ++i) {
        QList<QStandardItem *> items;
        QStandardItem *item = new QStandardItem(QString(config.InputParam.SendDataList[i]));
        items.append(item);
        model->appendRow(items);
    }
    QStyleWithButtonDelegate *delegate = new QStyleWithButtonDelegate(this);
    delegate->port = this->serviceAdapter->serialService;
    // 将模型设置给 tableView
    this->ui->tableView->setItemDelegate(delegate);
    this->ui->tableView->setModel(model);
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
        this->serviceAdapter->logService->setTextLog(this->ui->log_text, "时间间隔不能为空！", Inner, Error);
        return;
    }
    uint interval;
    bool flag = isQStringToUint(sendperiodTime, &interval);
    if (!flag)
    {
        this->serviceAdapter->logService->setTextLog(this->ui->log_text, "时间间隔格式错误！", Inner, Error);
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
            sendDataTimer = NULL;
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
    config.Baudrate = this->serviceAdapter->serialService->mathBaudRate(this->ui->comboBox_BaudRate->currentText());
    config.DataBits = this->serviceAdapter->serialService->mathDataBits(this->ui->comboBox_DateBits->currentText());
    config.StopBits = this->serviceAdapter->serialService->mathStopBits(this->ui->comboBox_StopBits->currentText());
    config.Parity = this->serviceAdapter->serialService->mathParity(this->ui->comboBox_Parity->currentText());
    config.PortName = this->ui->comPortBox->currentText();
    this->serviceAdapter->serialService->initSerialPortInstance(config);
    this->serviceAdapter->serialService->OpenPort();
    if (this->serviceAdapter->serialService->GetConnectStatus())
    {
        this->ui->btu_open_com->setEnabled(false);
        this->ui->btu_send_data->setEnabled(true);
        this->ui->btu_close_com->setEnabled(true);
        connect(this->serviceAdapter->serialService, &lscom_service::serialImp::serialRevDataSignal, this, &lscom::onPortDataReved);
        connect(this->serviceAdapter->serialService, &lscom_service::serialImp::serialSendDataSignal, this, &lscom::onPortDataSend);
    }
}

/**
 * @brief 关闭串口
 */
void lscom::on_btu_close_com_clicked()
{
    this->serviceAdapter->serialService->ClosePort();
    this->ui->btu_open_com->setEnabled(true);
    this->ui->btu_send_data->setEnabled(false);
    this->ui->btu_close_com->setEnabled(false);
    disconnect(this->serviceAdapter->serialService, &lscom_service::serialImp::serialRevDataSignal, this, &lscom::onPortDataReved);
    disconnect(this->serviceAdapter->serialService, &lscom_service::serialImp::serialSendDataSignal, this, &lscom::onPortDataSend);
}

/**
 * @brief 发送数据
 */
void lscom::on_btu_send_data_clicked()
{
    this->serviceAdapter->serialService->SendData(this->ui->text_send->toPlainText().toUtf8());
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
    this->serviceAdapter->serialService->setIsHexDisplay(checked);
}
/**
 * @brief hex发送勾选事件
 * @param checked
 */
void lscom::on_cb_hex_send_clicked(bool checked)
{
    this->serviceAdapter->serialService->setIsHexSend(checked);
}

/**
 * @brief 定时发送勾选事件
 * @param checked
 */
void lscom::on_cb_time_send_clicked(bool checked)
{
    if (this->serviceAdapter->serialService->GetConnectStatus())
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

/**
 * @brief 保存参数
 */
void lscom::on_btu_set_param_clicked()
{
    Config config;
    config.InputParam.SendAreaData = this->ui->text_send->toPlainText();
    config.InputParam.SendInterval = this->ui->sendperiod->text();
    QList<QString> list;
    for (int i = 0; i < this->ui->tableView->model()->rowCount(); ++i) {
        auto index = this->ui->tableView->model()->index(i,0);
        auto data = this->ui->tableView->model()->data(index);
        list.append(data.toString());
    }
    config.InputParam.SendDataList = list;
    this->serviceAdapter->configService->WriteConfigToFile(config);
    this->serviceAdapter->logService->setTextLog(this->ui->log_text, "保存成功", Inner, Info);
}

lscom::~lscom()
{
    this->distoryTimer();
    delete serviceAdapter;
    delete ui;
}

/**
 * @brief 接收数据量注册方法
 * @param data
 */
void lscom::onPortDataReved(long data)
{
    setNumOnLabel(recConterLabel, "R:", recConter += data);
}

/**
 * @brief 发送数据量注册方法
 * @param data
 */
void lscom::onPortDataSend(long data)
{
    setNumOnLabel(sendConterLabel, "S:", sendConter += data);
}

void lscom::on_cB_rev_to_file_clicked(bool checked)
{
    this->serviceAdapter->serialService->setIsRevDataToFile(checked);
}

