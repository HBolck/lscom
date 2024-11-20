#include "serial_imp.h"
#include "qserialport.h"

serialImp::serialImp() {
    //初始化的时候定义端口类型
    this->portType = Serial;
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
        qDebug() << "Port Name: " << info.portName();
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
    return  qslist;
}

QStringList serialImp::getSerialDataBits()
{
    QStringList qslist;
    qslist.append("5");
    qslist.append("6");
    qslist.append("7");
    qslist.append("8");
    return  qslist;
}

QStringList serialImp::getSerialStopBits()
{
    QStringList qslist;
    qslist.append("1");
    qslist.append("1.5");
    qslist.append("2");
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

serialImp::~serialImp()
{

}
