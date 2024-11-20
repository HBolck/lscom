#ifndef SERIAL_IMP_H
#define SERIAL_IMP_H
#include "iport.h"
#include <QSerialPort>
#include <QSerialPortInfo>
class serialImp : public IPort
{
public:
    serialImp();


    // IPort interface
public:
    std::string getDescription();

public:
    QStringList  getSerialPorts();
    QStringList  getSerialBundRates();
    QStringList  getSerialDataBits();
    QStringList  getSerialStopBits();
    QStringList  getSerialParity();

public:
    ~serialImp();
};

#endif // SERIAL_IMP_H
