#include "lscom.h"
#include "ui_lscom.h"

lscom::lscom(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lscom)
{
    ui->setupUi(this);

    //构建服务类对象
    this->serial = new serialImp();
    this->log = new LogService();

    initView();
    log->setTextLog(this->ui->log_text,"启动初始化结束");
}

void lscom::initView()
{
    ui->log_text->setReadOnly(true);
    ui->comPortBox->clear();
    ui->comPortBox->addItems(serial->getSerialPorts());
    ui->comboBox_BaudRate->addItems(serial->getSerialBundRates());
    ui->comboBox_DateBits->addItems(serial->getSerialDataBits());
    ui->comboBox_StopBits->addItems(serial->getSerialStopBits());
    ui->comboBox_Parity->addItems(serial->getSerialParity());
}



lscom::~lscom()
{
    delete serial;
    delete log;
    delete ui;
}


/**
 * @brief lscom::on_btu_open_com_clicked
 */
void lscom::on_btu_open_com_clicked()
{

}

/**
 * @brief lscom::on_btu_close_com_clicked
 */
void lscom::on_btu_close_com_clicked()
{

}

