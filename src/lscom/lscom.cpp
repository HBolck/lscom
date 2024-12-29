#include "lscom.h"
#include "ui_lscom.h"

lscom::lscom(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::lscom)
{
    ui->setupUi(this);
    // 构建服务类对象
    this->serviceAdapter = new lscom_service::ServiceAdapter(this->ui->log_text);
    initView();    
}
// ******************** 开始：页面初始化 ********************
/**
 * @brief 初始化页面
 */
void lscom::initView()
{
    this->window()->setWindowTitle(GLOBAL_TITLE);
    this->ui->btu_open_com->setText(GLOBAL_OPEN_CONTEXT);
    initStatusBar();
    // 设置日志区域不可编辑
    ui->log_text->setReadOnly(true);
    this->ui->btu_open_com->setEnabled(true);
    this->ui->btu_send_data->setEnabled(false);
    Config config = this->serviceAdapter->configService->InitConfigFile();

    // 加载子项面板对象
    loadChildPanel();
    // 加载配置缓存内容
    loadConfig(config);
    loadProtocolList();
    this->serviceAdapter->logService->setTextLog(this->ui->log_text, "======欢迎使用lscom工具======", Inner, Info);
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
    this->version->setText("v1.2.3");
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
    SetNumOnLabel(this->recConterLabel, "R:", recConter);
    SetNumOnLabel(this->sendConterLabel, "S:", sendConter);
    this->ui->statusbar->addWidget(recConterLabel);
    this->ui->statusbar->addWidget(sendConterLabel);
}

/**
 * @brief 初始化数据表格
 */
void lscom::initTalbeView(const Config &config)
{
    // 创建 QStandardItemModel 对象来存储数据
    QStandardItemModel *model = new QStandardItemModel;
    // 设置表头
    model->setHorizontalHeaderLabels(QStringList() << "数据" << "操作");
    // 向模型中添加数据
    for (int i = 0; i < config.InputParam.SendDataList.count(); ++i)
    {
        QList<QStandardItem *> items;
        QStandardItem *item = new QStandardItem(QString(config.InputParam.SendDataList[i]));
        items.append(item);
        model->appendRow(items);
    }
    QStyleWithButtonDelegate *delegate = new QStyleWithButtonDelegate(this);
    //将协议对象指针传递进委托模型中
    delegate->port = this->serviceAdapter->strategyFactory->PotocolImp;
    // 将模型设置给 tableView
    this->ui->tableView->setItemDelegate(delegate);
    this->ui->tableView->setModel(model);
}

/**
 * @brief 加载导入的文件
 * @param fileName
 */
void lscom::loadImportFile(const QString &fileName)
{
    if (!fileName.isEmpty() && !fileName.isNull())
    {
        this->ui->importFileName->setText(fileName);
        if (CheckFileExist(fileName))
        {
            // 导入缓存
            this->importFileContentCache = ReadFileContentList(fileName);
            // 显示页面中文本内容
            this->ui->text_file_area->setText(ReadFileContents(fileName));
            // 将文件路径缓存到内存中
            this->importFilePathCache = fileName;
        }
    }
}

/**
 * @brief 加载配置信息
 * @param config
 */
void lscom::loadConfig(const Config &config)
{
    this->ui->sendperiod->setText(config.InputParam.SendInterval);                                                                               // 加载已有的定时发送间隔
    this->ui->text_send->setText(config.InputParam.SendAreaData);                                                                                // 加载已有的发送区内容
    this->loadImportFile(config.InputParam.ImportFilePath);                                                                                      // 导入已有的文件内容
    this->ui->cB_pLineSend_loop->setChecked(!StringIsNllOrEmpty(config.InputParam.IsFileLoopSend) && (config.InputParam.IsFileLoopSend == "1")); // 设置是否循环发送文件内容
    this->ui->cB_pLineSend->setChecked(!StringIsNllOrEmpty(config.InputParam.IsPLineSend) && (config.InputParam.IsPLineSend == "1"));            // 设置是否逐行发送文件内容
    this->ui->pLineInterval->setText(config.InputParam.FileSendLineInterval);
    // 初始化表格数据内容
    initTalbeView(config);
}

/**
 * @brief 加载子面板
 */
void lscom::loadChildPanel()
{
    // 初始化面板
    this->serialPanel = new SerialPortConfigPanel(this->ui->stackedWidget);
    // std::map<Protocol, QWidget *> panels = {{SerialPort, this->serialPanel}};
    this->serviceAdapter->strategyFactory->InitConfigPanel(
        {{SerialPort, this->serialPanel} /*, {TcpServer, this->tcpPanel}*/}); // 填充配置面板对象

    this->serviceAdapter->strategyFactory->PointToPotocol(SerialPort); // 默认指向串口协议
}

/**
 * @brief 加载协议内容
 */
void lscom::loadProtocolList()
{
    this->ui->protocolList->addItem("SerialPort");
    // this->ui->protocolList->addItem("TcpService");
    // this->ui->protocolList->addItem("TcpClient");
    // this->ui->protocolList->addItem("UDP");
}
// ******************** 结束：页面初始化 ********************

// ******************** 开始：定时器 ********************

/**
 * @brief 初始化定时器
 */
void lscom::initTimer()
{
    QString sendperiodTime = this->ui->sendperiod->text();
    if (sendperiodTime.isEmpty())
    {
        this->serviceAdapter->logService->setTextLog(this->ui->log_text, "时间间隔不能为空！", Inner, Error);
        return;
    }
    uint interval;
    bool flag = IsQStringToUint(sendperiodTime, &interval);
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
// ******************** 结束：定时器 ********************

// ******************** 开始：页面事件响应 ********************

void lscom::on_protocolList_currentIndexChanged(int index)
{
    ClearWidgetChildren(this->ui->stackedWidget);
    switch (index)
    {
    case 0:
        // 将配置面板插入到页面容器中
        this->ui->stackedWidget->addWidget(this->serialPanel);
        this->serviceAdapter->strategyFactory->PointToPotocol(SerialPort); // 指向串口协议
        break;
    case 1:
        // 将配置面板插入到页面容器中
        // this->ui->stackedWidget->addWidget(this->tcpPanel);
        break;
    case 2:
        break;
    default:
        break;
    }
}

/**
 * @brief 开启端口
 */
void lscom::on_btu_open_com_clicked()
{
    if (this->serviceAdapter->strategyFactory->PotocolImp->GetConnectStatus())
    {
        this->serviceAdapter->strategyFactory->PotocolImp->ClosePort();
        this->ui->btu_send_data->setEnabled(false);
        disconnect(this->serviceAdapter->strategyFactory->PotocolImp, &lscom_port::IPortBase::RevDataLengthSignal, this, &lscom::onPortDataReved);
        disconnect(this->serviceAdapter->strategyFactory->PotocolImp, &lscom_port::IPortBase::SendDataLengthSignal, this, &lscom::onPortDataSend);
        this->ui->btu_open_com->setText(GLOBAL_OPEN_CONTEXT);
    }
    else
    {
        this->serviceAdapter->strategyFactory->PotocolImp->OpenPort();
        if (this->serviceAdapter->strategyFactory->PotocolImp->GetConnectStatus())
        {
            this->ui->btu_send_data->setEnabled(true);
            connect(this->serviceAdapter->strategyFactory->PotocolImp, &lscom_port::IPortBase::RevDataLengthSignal, this, &lscom::onPortDataReved);
            connect(this->serviceAdapter->strategyFactory->PotocolImp, &lscom_port::IPortBase::SendDataLengthSignal, this, &lscom::onPortDataSend);
            this->ui->btu_open_com->setText(GLOBAL_CLOSE_CONTEXT);
        }
    }
}

/**
 * @brief 发送数据
 */
void lscom::on_btu_send_data_clicked()
{
    this->serviceAdapter->strategyFactory->PotocolImp->SendData(this->ui->text_send->toPlainText().toUtf8());
}

/**
 * @brief 清空窗口
 */
void lscom::on_btu_clear_log_text_clicked()
{
    this->ui->log_text->clear();
    recConter = 0;
    SetNumOnLabel(recConterLabel, "R:", 0);
}

/**
 * @brief 清空发送区内容
 */
void lscom::on_btu_clear_send_text_clicked()
{
    this->ui->text_send->clear();
    sendConter = 0;
    SetNumOnLabel(sendConterLabel, "S:", 0);
}

/**
 * @brief hex显示勾选事件
 * @param checked
 */
void lscom::on_cb_hex_display_clicked(bool checked)
{
    this->serviceAdapter->strategyFactory->PotocolImp->setIsHexDisplay(checked);
}
/**
 * @brief hex发送勾选事件
 * @param checked
 */
void lscom::on_cb_hex_send_clicked(bool checked)
{
    this->serviceAdapter->strategyFactory->PotocolImp->setIsHexSend(checked);
}

/**
 * @brief 定时发送勾选事件
 * @param checked
 */
void lscom::on_cb_time_send_clicked(bool checked)
{
    if (this->serviceAdapter->strategyFactory->PotocolImp->GetConnectStatus())
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
 * @brief 接收数据到文件勾选
 * @param checked
 */
void lscom::on_cB_rev_to_file_clicked(bool checked)
{
    this->serviceAdapter->strategyFactory->PotocolImp->setIsRevDataToFile(checked);
}

/**
 * @brief 保存参数
 */
void lscom::on_btu_set_param_clicked()
{
    Config config;
    config.InputParam.SendAreaData = this->ui->text_send->toPlainText();
    config.InputParam.SendInterval = this->ui->sendperiod->text();
    config.InputParam.ImportFilePath = this->importFilePathCache;
    config.InputParam.IsPLineSend = this->ui->cB_pLineSend->isChecked() ? "1" : "0";         // 是否逐行发送
    config.InputParam.IsFileLoopSend = this->ui->cB_pLineSend_loop->isChecked() ? "1" : "0"; // 是否循环发送
    config.InputParam.FileSendLineInterval = this->ui->pLineInterval->text();                // 逐行发送间隔
    QList<QString> list;
    for (int i = 0; i < this->ui->tableView->model()->rowCount(); ++i)
    {
        auto index = this->ui->tableView->model()->index(i, 0);
        auto data = this->ui->tableView->model()->data(index);
        list.append(data.toString());
    }
    config.InputParam.SendDataList = list;
    this->serviceAdapter->configService->WriteConfigToFile(config);
    this->serviceAdapter->logService->setTextLog(this->ui->log_text, "保存成功", Inner, Info);
}

/**
 * @brief 打开文件
 */
void lscom::on_btu_send_open_file_clicked()
{
    this->loadImportFile(QFileDialog::getOpenFileName(nullptr, "打开数据文件", "", GLOBAL_IMPORT_FILE_EXT));
}

/**
 * @brief 发送文件
 */
void lscom::on_btu_send_file_clicked()
{
    if (this->importFileContentCache.size() > 0)
    {
        if (this->serviceAdapter->strategyFactory->PotocolImp->GetConnectStatus())
        {
            // 逐行发送
            if (this->ui->cB_pLineSend->isChecked())
            {
                uint interval;
                QString sendperiodTime = this->ui->pLineInterval->text();
                if (sendperiodTime.isEmpty())
                {
                    this->serviceAdapter->logService->setTextLog(this->ui->log_text, "时间间隔不能为空！[默认使用1000ms作为之间间隔]", Inner, Error);
                    interval = 1000;
                }
                bool flag = IsQStringToUint(sendperiodTime, &interval);
                if (!flag)
                {
                    this->serviceAdapter->logService->setTextLog(this->ui->log_text, "时间间隔格式错误！[默认使用1000ms作为之间间隔]", Inner, Error);
                    interval = 1000;
                }
                QElapsedTimer timer;
                for (const QString &data : importFileContentCache)
                {
                    timer.restart();
                    while (timer.elapsed() < interval)
                    {
                        QCoreApplication::processEvents(); // 用于处理当前线程中的待处理事件 保证主线程不阻塞
                    }
                    this->serviceAdapter->strategyFactory->PotocolImp->SendData(data.toUtf8());

                    // 这个操作是异步的 这里不适合
                    //  QTimer::singleShot(interval, this, [=]()
                    //                     { this->serviceAdapter->serialService->SendData(data.toUtf8()); });
                }
            }
            else // 全量发送
            {
                this->serviceAdapter->strategyFactory->PotocolImp->SendData(this->ui->text_file_area->toPlainText().toUtf8());
            }
        }
        else
        {
            this->serviceAdapter->logService->setTextLog(this->ui->log_text, "端口未打开！", Inner, Error);
        }
    }
    else
    {
        this->serviceAdapter->logService->setTextLog(this->ui->log_text, "请选择文件后重试！", Inner, Warning);
    }
}

/**
 * @brief 清空文件信息
 */
void lscom::on_btu_clear_file_clicked()
{
    this->ui->importFileName->clear();
    this->ui->text_file_area->clear();
    this->importFilePathCache.clear();
}

// ******************** 结束：页面事件响应 ********************

// ******************** 开始：信号事件注册 ********************

/**
 * @brief 接收数据量注册方法
 * @param data
 */
void lscom::onPortDataReved(long data)
{
    SetNumOnLabel(recConterLabel, "R:", recConter += data);
}

/**
 * @brief 发送数据量注册方法
 * @param data
 */
void lscom::onPortDataSend(long data)
{
    SetNumOnLabel(sendConterLabel, "S:", sendConter += data);
}

// ******************** 结束：信号事件注册 ********************

lscom::~lscom()
{
    ClearWidgetChildren(this->ui->stackedWidget, true);
    this->distoryTimer();
    delete serviceAdapter;
    delete ui;
}



