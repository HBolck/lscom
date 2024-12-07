#include "serialportconfigpanel.h"
#include "ui_serialportconfigpanel.h"

SerialPortConfigPanel::SerialPortConfigPanel(QWidget *parent)
    : QWidget(parent), ui(new Ui::SerialPortConfigPanel)
{
    ui->setupUi(this);
}

SerialPortConfigPanel::~SerialPortConfigPanel()
{
    delete ui;
}

QSerialPort::BaudRate SerialPortConfigPanel::mathBaudRate(const QString &str)
{
    auto it = baudRateMap.find(str);
    if (it != baudRateMap.end())
    {
        return it->second;
    }
    else
    {
        // 处理无效的输入
        return QSerialPort::Baud9600;
    }
}

QSerialPort::DataBits SerialPortConfigPanel::mathDataBits(const QString &str)
{
    auto it = dataBitsMap.find(str);
    if (it != dataBitsMap.end())
    {
        return it->second;
    }
    else
    {
        // 处理无效的输入
        return QSerialPort::Data8;
    }
}

QSerialPort::StopBits SerialPortConfigPanel::mathStopBits(const QString &str)
{
    auto it = stopBitsMap.find(str);
    if (it != stopBitsMap.end())
    {
        return it->second;
    }
    else
    {
        // 处理无效的输入
        return QSerialPort::OneStop;
    }
}

QSerialPort::Parity SerialPortConfigPanel::mathParity(const QString &str)
{
    auto it = parityMap.find(str);
    if (it != parityMap.end())
    {
        return it->second;
    }
    else
    {
        // 处理无效的输入
        return QSerialPort::NoParity;
    }
}

QStringList SerialPortConfigPanel::getSerialPorts()
{
    QStringList qSlist;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qSlist.append(info.portName());
    }
    return qSlist;
}

QStringList SerialPortConfigPanel::getSerialBundRates()
{
    QStringList qslist;
    qslist.append("1200");
    qslist.append("2400");
    qslist.append("4800");
    qslist.append("9600");
    qslist.append("19200");
    qslist.append("38400");
    qslist.append("57600");
    qslist.append("115200");
    return qslist;
}

QStringList SerialPortConfigPanel::getSerialDataBits()
{
    QStringList qslist;
    for (const auto &piar : dataBitsMap)
    {
        qslist.append(piar.first);
    }
    return qslist;
}

QStringList SerialPortConfigPanel::getSerialStopBits()
{
    QStringList qslist;
    for (const auto &piar : stopBitsMap)
    {
        qslist.append(piar.first);
    }
    return qslist;
}

QStringList SerialPortConfigPanel::getSerialParity()
{
    QStringList qslist;
    qslist.append("None");
    qslist.append("Odd");
    qslist.append("Even");
    return qslist;
}

SerialPortConfig SerialPortConfigPanel::GetSerialPortConfig()
{
    SerialPortConfig config;
    config.Baudrate = mathBaudRate(this->ui->comboBox_BaudRate->currentText());
    config.DataBits = mathDataBits(this->ui->comboBox_DateBits->currentText());
    config.StopBits = mathStopBits(this->ui->comboBox_StopBits->currentText());
    config.Parity = mathParity(this->ui->comboBox_Parity->currentText());
    config.PortName = this->ui->comPortBox->currentText();
    return config;
}

void SerialPortConfigPanel::InitParam()
{
    // 初始化串口参数
    ui->comPortBox->clear();
    ui->comPortBox->addItems(this->getSerialPorts());
    ui->comboBox_BaudRate->addItems(this->getSerialBundRates());
    ui->comboBox_BaudRate->setCurrentIndex(3); // 9600
    ui->comboBox_DateBits->addItems(this->getSerialDataBits());
    ui->comboBox_DateBits->setCurrentIndex(3); // 8
    ui->comboBox_StopBits->addItems(this->getSerialStopBits());
    ui->comboBox_Parity->addItems(this->getSerialParity());
}
