#include "serial_imp.h"
#include "qserialport.h"

serialImp::serialImp()
{

}

serialImp::serialImp(LogService* log,QTextEdit *textEdit) {

    this->log = log;
    this->textEdit = textEdit;
}

std::string serialImp::getDescription()
{
    return "串口类型的服务";
}

QStringList serialImp::getSerialPorts()
{
    QStringList qSlist;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qSlist.append(info.portName());
        // qDebug() << "Port Name: " << info.portName();
    }
    return qSlist;
}

QStringList serialImp::getSerialBundRates()
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
    return  qslist;
}

QStringList serialImp::getSerialDataBits()
{
    QStringList qslist;
    for(const auto& piar : dataBitsMap){
        qslist.append(piar.first);
    }
    return  qslist;
}

QStringList serialImp::getSerialStopBits()
{
    QStringList qslist;
    for(const auto& piar : stopBitsMap){
        qslist.append(piar.first);
    }
    return  qslist;
}

QStringList serialImp::getSerialParity()
{
    QStringList qslist;
    qslist.append("None");
    qslist.append("Odd");
    qslist.append("Even");
    return  qslist;
}


/**
 * @brief serialImp::mathBaudRate
 * @param baudRateStr
 * @return
 */
QSerialPort::BaudRate serialImp::mathBaudRate(const QString &baudRateStr)
{
    auto it = baudRateMap.find(baudRateStr);
    if (it!= baudRateMap.end()) {
        return it->second;
    } else {
        // 处理无效的输入
        return QSerialPort::Baud9600;
    }
}


QSerialPort::DataBits serialImp::mathDataBits(const QString &str)
{
    auto it = dataBitsMap.find(str);
    if (it!= dataBitsMap.end()) {
        return it->second;
    } else {
        // 处理无效的输入
        return QSerialPort::Data8;
    }
}

QSerialPort::StopBits serialImp::mathStopBits(const QString &str)
{
    auto it = stopBitsMap.find(str);
    if (it!= stopBitsMap.end()) {
        return it->second;
    } else {
        // 处理无效的输入
        return QSerialPort::OneStop;
    }
}

QSerialPort::Parity serialImp::mathParity(const QString &str)
{
    auto it = parityMap.find(str);
    if (it!= parityMap.end()) {
        return it->second;
    } else {
        // 处理无效的输入
        return QSerialPort::NoParity;
    }
}

void serialImp::initSerialPortInstance(SerialPortConfig config)
{
    this->_serialPort.setBaudRate(config.Baudrate);
    this->_serialPort.setDataBits(config.DataBits);
    this->_serialPort.setStopBits(config.StopBits);
    this->_serialPort.setParity(config.Parity);
    this->_serialPort.setPortName(config.PortName);
    this->_isConfiged = true;
}

bool serialImp::isConnected(){
    return this->_serialPort.isOpen();
}

void serialImp::openPort()
{
    if((this->isConnected() == false) && this->_isConfiged){
        try {
            //设置串口的打开方式（可读可写）
            this->_serialPort.open(QIODevice::ReadWrite);
            if(this->isConnected()){
                log->setTextLog(this->textEdit,this->_serialPort.portName().append("端口打开成功").toUtf8().constData(),Inner,Info);
                connect(&_serialPort, &QSerialPort::readyRead, this, &serialImp::handleReadyRead);
            }
        } catch (...) {
            if(log != NULL){
                try {
                    std::rethrow_exception(std::current_exception());
                } catch (const char* exceptionMessage) {
                    std::cout << "Caught exception: " << exceptionMessage << std::endl;
                    log->setTextLog(this->textEdit,exceptionMessage,Inner,Error);

                } catch (const std::exception& e) {
                    std::cout << "Caught standard exception: " << e.what() << std::endl;
                    log->setTextLog(this->textEdit,e.what(),Inner,Error);
                }
            }
        }

    }
}

void serialImp::closePort()
{
    if(this->isConnected()){
        this->_serialPort.close();
        log->setTextLog(this->textEdit,"端口已关闭",Inner,Error);
        disconnect(&_serialPort, &QSerialPort::readyRead, this, &serialImp::handleReadyRead);
    }else{
        log->setTextLog(this->textEdit,"端口没有打开",Inner,Error);
    }

}

/**
 * @brief serialImp::sendData
 * @param data
 */
void serialImp::sendData(QByteArray data)
{
    this->_serialPort.write(data);
}

void serialImp::handleReadyRead()
{
    QSerialPort *serial = qobject_cast<QSerialPort *>(sender());
    if (serial)
    {
        QByteArray data = serial->readAll();
        qDebug() << "Received data: " << data;
        log->setTextLog(this->textEdit,data,Rev,Info);
    }
}


serialImp::~serialImp()
{
    this->closePort();
    // delete _serialPort;
}




