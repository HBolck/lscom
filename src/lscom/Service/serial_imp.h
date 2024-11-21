#ifndef SERIAL_IMP_H
#define SERIAL_IMP_H
#include <iostream>
#include <windows.h>
#include <QMainWindow>
#include <QDebug>
#include <map>
#include <QObject>
#include <QCoreApplication>
#include "Service/logservice.h"
#include <QSerialPort>
#include <QSerialPortInfo>


/**
 * @brief The SerialPortConfig
 */
struct SerialPortConfig{
    /**
     * @brief Baudrate
     */
    QSerialPort::BaudRate Baudrate;
    /**
     * @brief DataBits
     */
    QSerialPort::DataBits DataBits;
    /**
     * @brief StopBits
     */
    QSerialPort::StopBits StopBits;
    /**
     * @brief Parity
     */
    QSerialPort::Parity Parity;

    /**
     * @brief PortName
     */
    QString PortName;
};

class serialImp :public QObject
{    
    Q_OBJECT

public:
    serialImp();
    serialImp(LogService* log,QTextEdit *textEdit);
    std::string getDescription();
    QStringList  getSerialPorts();
    QStringList  getSerialBundRates();
    QStringList  getSerialDataBits();
    QStringList  getSerialStopBits();
    QStringList  getSerialParity();

    /**
     * @brief mathBaudRate
     * @param str
     * @return
     */
    QSerialPort::BaudRate mathBaudRate(const QString &str);
    /**
     * @brief mathDataBits
     * @param str
     * @return
     */
    QSerialPort::DataBits mathDataBits(const QString &str);
    /**
     * @brief mathStopBits
     * @param str
     * @return
     */
    QSerialPort::StopBits mathStopBits(const QString &str);
    /**
     * @brief mathParity
     * @param str
     * @return
     */
    QSerialPort::Parity mathParity(const QString &str);
    /**
     * @brief 初始化串口
     */
    void initSerialPortInstance(SerialPortConfig config);
    bool isConnected();
    void openPort();
    void closePort();
    void sendData(QByteArray data);
    ~serialImp();


public slots:
    /**
     * @brief handleReadyRead
     */
    void handleReadyRead();

private:
    /**
     * @brief 内部的串口对象
     */
    QSerialPort _serialPort;
    LogService* log;
    QTextEdit *textEdit;
    /**
     * @brief 是否被配置过
     */
    bool _isConfiged;

    /**
     * @brief baudRateMap
     */
    std::map<QString, QSerialPort::BaudRate> baudRateMap = {
        {"1200", QSerialPort::Baud1200},
        {"2400", QSerialPort::Baud2400},
        {"4800", QSerialPort::Baud4800},
        {"9600", QSerialPort::Baud9600},
        {"19200", QSerialPort::Baud19200},
        {"38400", QSerialPort::Baud38400},
        {"57600", QSerialPort::Baud57600},
        {"115200", QSerialPort::Baud115200}
    };

    /**
     * @brief dataBitsMap
     */
    std::map<QString, QSerialPort::DataBits> dataBitsMap = {
                                                            {"5", QSerialPort::Data5},
                                                            {"6", QSerialPort::Data6},
                                                            {"7", QSerialPort::Data7},
                                                            {"8", QSerialPort::Data8},
                                                            };

    /**
     * @brief stopBitsMap
     */
    std::map<QString, QSerialPort::StopBits> stopBitsMap = {
                                                            {"1", QSerialPort::OneStop},
                                                            {"1.5", QSerialPort::OneAndHalfStop },
                                                            {"2", QSerialPort::TwoStop },
                                                            };

    /**
     * @brief parityMap
     */
    std::map<QString, QSerialPort::Parity> parityMap = {
        {"None", QSerialPort::NoParity},
        {"Odd", QSerialPort::EvenParity},
        {"Even", QSerialPort::OddParity}
    };

};

#endif // SERIAL_IMP_H
