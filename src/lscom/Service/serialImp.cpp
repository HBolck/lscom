#include "serialImp.h"
#include "qserialport.h"
#include <iostream>

lscom_service::serialImp::serialImp()
{
    this->protType = RTU;
}

lscom_service::serialImp::serialImp(LogService *log, QTextEdit *textEdit)
{
    this->protType = RTU;
    this->log = log;
    this->textEdit = textEdit;
}

bool lscom_service::serialImp::isHexSend() const
{
    return _isHexSend;
}

void lscom_service::serialImp::setIsHexSend(bool newIsHexSend)
{
    _isHexSend = newIsHexSend;
}

bool lscom_service::serialImp::isHexDisplay() const
{
    return _isHexDisplay;
}

void lscom_service::serialImp::setIsHexDisplay(bool newIsHexDisplay)
{
    _isHexDisplay = newIsHexDisplay;
}

void lscom_service::serialImp::setIsRevDataToFile(bool newIsRevDataToFile)
{
    isRevDataToFile = newIsRevDataToFile;
}

void lscom_service::serialImp::setConfigPanel(QWidget *widget)
{
    this->serialPanel = qobject_cast<SerialPortConfigPanel *>(widget);
    if (!serialPanel)
    {
        log->setTextLog(this->textEdit, "初始化配置面板失败，检查代码", Inner, Error);
        return;
    }
}

/**
 * @brief 是否连接
 * @return
 */
bool lscom_service::serialImp::GetConnectStatus()
{
    return this->_serialPort.isOpen();
}

PortType lscom_service::serialImp::getProtType() const
{
    return this->protType;
}

/**
 * @brief 打开串口
 */
void lscom_service::serialImp::OpenPort()
{
    auto config = this->serialPanel->GetSerialPortConfig();
    this->_serialPort.setBaudRate(config.Baudrate);
    this->_serialPort.setDataBits(config.DataBits);
    this->_serialPort.setStopBits(config.StopBits);
    this->_serialPort.setParity(config.Parity);
    this->_serialPort.setPortName(config.PortName);
    this->_isConfiged = true;

    if ((this->GetConnectStatus() == false) && this->_isConfiged)
    {
        try
        {
            // 设置串口的打开方式（可读可写）
            this->_serialPort.open(QIODevice::ReadWrite);
            if (this->GetConnectStatus())
            {
                log->setTextLog(this->textEdit, this->_serialPort.portName().append("端口打开成功").toUtf8().constData(), Inner, Info);
                connect(&_serialPort, &QSerialPort::readyRead, this, &serialImp::handleReadyRead);
                // connect(&_serialPort, &QSerialPort::readyRead, this, &lscom::handleReadyRead);
            }
            else
            {
                log->setTextLog(this->textEdit,
                                this->_serialPort.portName()
                                    .append("端口打开失败！\r检查端口是否被占用或者接触不良")
                                    .toUtf8()
                                    .constData(),
                                Inner,
                                Error);
            }
        }
        catch (...)
        {
            if (log != NULL)
            {
                try
                {
                    std::rethrow_exception(std::current_exception());
                }
                catch (const char *exceptionMessage)
                {
                    std::cout << "Caught exception: " << exceptionMessage << std::endl;
                    log->setTextLog(this->textEdit, exceptionMessage, Inner, Error);
                }
                catch (const std::exception &e)
                {
                    std::cout << "Caught standard exception: " << e.what() << std::endl;
                    log->setTextLog(this->textEdit, e.what(), Inner, Error);
                }
            }
        }
    }
}

/**
 * @brief 关闭端口
 */
void lscom_service::serialImp::ClosePort()
{
    if (this->GetConnectStatus())
    {
        this->_serialPort.close();
        log->setTextLog(this->textEdit, "端口已关闭", Inner, Error);
        disconnect(&_serialPort, &QSerialPort::readyRead, this, &serialImp::handleReadyRead);
    }
    else
    {
        log->setTextLog(this->textEdit, "端口没有打开", Inner, Error);
    }
}

/**
 * @brief 发送数据
 * @param data
 */
void lscom_service::serialImp::SendData(QByteArray data)
{
    if (this->GetConnectStatus())
    {
        if (data.isEmpty())
            return;
        if (_isHexSend)
        {
            QString hexString;
            for (char byte : data)
            {
                hexString.append(QString("%1 ").arg(static_cast<quint8>(byte), 2, 16, QChar('0').toUpper()));
            }
            this->_serialPort.write(hexString.toUtf8());
        }
        else
            this->_serialPort.write(data);
        log->setTextLog(textEdit, data, Send, Info);
        // 激发信号
        emit this->SendDataLengthSignal(data.size());
    }
}

/**
 * @brief 接收数据内容
 */
void lscom_service::serialImp::handleReadyRead()
{
    QSerialPort *serial = qobject_cast<QSerialPort *>(sender());
    if (serial)
    {
        QByteArray data = serial->readAll();
        // qDebug() << "Received data: " << data;
        if (_isHexDisplay)
        {
            QString hexString;
            for (char byte : data)
            {
                hexString.append(QString("%1 ").arg(static_cast<quint8>(byte), 2, 16, QChar('0').toUpper()));
            }
            log->setTextLog(this->textEdit, hexString.toUtf8().constData(), Rev, Info);
        }
        else
        {
            log->setTextLog(this->textEdit, data, Rev, Info);
        }
        emit this->RevDataLengthSignal(data.size());
        if (this->isRevDataToFile)
        {
            log->writeLogToFile(data, "REV", Info);
        }
    }
}

lscom_service::serialImp::~serialImp()
{
    this->ClosePort();
}
