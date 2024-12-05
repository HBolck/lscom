#include "serialportconfigpanel.h"
#include "ui_serialportconfigpanel.h"

SerialPortConfigPanel::SerialPortConfigPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialPortConfigPanel)
{
    ui->setupUi(this);
}

SerialPortConfigPanel::~SerialPortConfigPanel()
{
    delete ui;
}

void SerialPortConfigPanel::setSerialImp(lscom_service::serialImp *newSerialImp)
{
    serialImp = newSerialImp;
    initSerialPortConfig();
}

SerialPortConfig SerialPortConfigPanel::GetSerialPortConfig()
{
    SerialPortConfig config;
    config.Baudrate = this->serialImp->mathBaudRate(this->ui->comboBox_BaudRate->currentText());
    config.DataBits = this->serialImp->mathDataBits(this->ui->comboBox_DateBits->currentText());
    config.StopBits = this->serialImp->mathStopBits(this->ui->comboBox_StopBits->currentText());
    config.Parity = this->serialImp->mathParity(this->ui->comboBox_Parity->currentText());
    config.PortName = this->ui->comPortBox->currentText();
    return config;
}

void SerialPortConfigPanel::initSerialPortConfig()
{
    // 初始化串口参数
    ui->comPortBox->clear();
    ui->comPortBox->addItems(this->serialImp->getSerialPorts());
    ui->comboBox_BaudRate->addItems(this->serialImp->getSerialBundRates());
    ui->comboBox_BaudRate->setCurrentIndex(3); // 9600
    ui->comboBox_DateBits->addItems(this->serialImp->getSerialDataBits());
    ui->comboBox_DateBits->setCurrentIndex(3); // 8
    ui->comboBox_StopBits->addItems(this->serialImp->getSerialStopBits());
    ui->comboBox_Parity->addItems(this->serialImp->getSerialParity());
}
