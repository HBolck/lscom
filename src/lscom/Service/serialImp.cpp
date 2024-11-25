#include "serialImp.h"
#include "qserialport.h"
#include <iostream>

lscom_service::serialImp::serialImp()
{
}

lscom_service::serialImp::serialImp(LogService *log, QTextEdit *textEdit)
{

    this->log = log;
    this->textEdit = textEdit;
}

std::string lscom_service::serialImp::getDescription()
{
    return "串口类型的服务";
}

QStringList lscom_service::serialImp::getSerialPorts()
{
    QStringList qSlist;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qSlist.append(info.portName());
        // qDebug() << "Port Name: " << info.portName();
    }
    return qSlist;
}

QStringList lscom_service::serialImp::getSerialBundRates()
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

QStringList lscom_service::serialImp::getSerialDataBits()
{
    QStringList qslist;
    for (const auto &piar : dataBitsMap)
    {
        qslist.append(piar.first);
    }
    return qslist;
}

QStringList lscom_service::serialImp::getSerialStopBits()
{
    QStringList qslist;
    for (const auto &piar : stopBitsMap)
    {
        qslist.append(piar.first);
    }
    return qslist;
}

QStringList lscom_service::serialImp::getSerialParity()
{
    QStringList qslist;
    qslist.append("None");
    qslist.append("Odd");
    qslist.append("Even");
    return qslist;
}

/**
 * @brief serialImp::mathBaudRate
 * @param baudRateStr
 * @return
 */
QSerialPort::BaudRate lscom_service::serialImp::mathBaudRate(const QString &baudRateStr)
{
    auto it = baudRateMap.find(baudRateStr);
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

QSerialPort::DataBits lscom_service::serialImp::mathDataBits(const QString &str)
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

QSerialPort::StopBits lscom_service::serialImp::mathStopBits(const QString &str)
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

QSerialPort::Parity lscom_service::serialImp::mathParity(const QString &str)
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

/**
 * @brief 初始化串口对象参数
 * @param config
 */
void lscom_service::serialImp::initSerialPortInstance(SerialPortConfig config)
{
    this->_serialPort.setBaudRate(config.Baudrate);
    this->_serialPort.setDataBits(config.DataBits);
    this->_serialPort.setStopBits(config.StopBits);
    this->_serialPort.setParity(config.Parity);
    this->_serialPort.setPortName(config.PortName);
    this->_isConfiged = true;
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
    return RTU;
}

/**
 * @brief 打开串口
 */
void lscom_service::serialImp::OpenPort()
{
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
void lscom_service::serialImp::sendData(QByteArray data)
{

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
}

void lscom_service::serialImp::handleReadyRead()
{
    QSerialPort *serial = qobject_cast<QSerialPort *>(sender());
    if (serial)
    {
        QByteArray data = serial->readAll();
        qDebug() << "Received data: " << data;

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
        emit this->serialRevDataSignal(data.size());
    }
}

lscom_service::serialImp::~serialImp()
{
    this->ClosePort();
}
