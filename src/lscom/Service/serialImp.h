#ifndef SERIALIMP_H
#define SERIALIMP_H

#include <windows.h>
#include <QMainWindow>
#include <QDebug>
#include <map>
#include <QObject>
#include <QCoreApplication>
#include "Port/PortBase.h"
#include "Service/logservice.h"
#include <QSerialPort>
#include <QSerialPortInfo>

/**
 * @brief The SerialPortConfig
 */
struct SerialPortConfig
{
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

namespace lscom_service
{

     class serialImp : public QObject, public lscom_port::IPortBase
     {
          Q_OBJECT

     public:
          serialImp();
          serialImp(LogService *log, QTextEdit *textEdit);
          std::string getDescription();
          QStringList getSerialPorts();
          QStringList getSerialBundRates();
          QStringList getSerialDataBits();
          QStringList getSerialStopBits();
          QStringList getSerialParity();

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

          ~serialImp();

          bool isHexDisplay() const;
          void setIsHexDisplay(bool newIsHexDisplay);

          bool isHexSend() const;
          void setIsHexSend(bool newIsHexSend);

          bool isRevDataToFile;
          void setIsRevDataToFile(bool newIsRevDataToFile);

     signals:
          /**
           * @brief 串口接收数据信号
           * @param data
           */
          void serialRevDataSignal(long data);
          /**
           * @brief 串口发送数据信号
           * @param data
           */
          void serialSendDataSignal(long data);

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
          LogService *log;
          QTextEdit *textEdit;
          /**
           * @brief 是否被配置过
           */
          bool _isConfiged;
          /**
           * @brief HEX显示
           */
          bool _isHexDisplay;
          /**
           * @brief HEX发送
           */
          bool _isHexSend;

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
              {"115200", QSerialPort::Baud115200}};

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
              {"1.5", QSerialPort::OneAndHalfStop},
              {"2", QSerialPort::TwoStop},
          };

          /**
           * @brief parityMap
           */
          std::map<QString, QSerialPort::Parity> parityMap = {
              {"None", QSerialPort::NoParity},
              {"Odd", QSerialPort::EvenParity},
              {"Even", QSerialPort::OddParity}};

          // IPortBase interface
     public:
          void OpenPort() override;
          void ClosePort() override;
          bool GetConnectStatus() override;
          PortType getProtType() const override;
          void SendData(QByteArray data) override;

     };
}

#endif // SERIALIMP_H
