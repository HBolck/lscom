#ifndef SERIALIMP_H
#define SERIALIMP_H

#include <windows.h>
#include <QMainWindow>
#include <QDebug>
#include <QObject>
#include <QCoreApplication>
#include "Port/PortBase.h"
#include "Service/logservice.h"
#include <QSerialPort>
#include <QSerialPortInfo>

namespace lscom_service
{

     class serialImp : public lscom_port::IPortBase
     {

          Q_OBJECT
     public:
          serialImp();
          serialImp(LogService *log, QTextEdit *textEdit);
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
          LogService *log;
          QTextEdit *textEdit;
          // IPortBase interface
     public:
          void OpenPort() override;
          void ClosePort() override;
          bool GetConnectStatus() override;
          PortType getProtType() const override;
          void SendData(QByteArray data) override;

          bool isHexDisplay() const override;
          void setIsHexDisplay(bool newIsHexDisplay) override;
          bool isHexSend() const override;
          void setIsHexSend(bool newIsHexSend) override;
          void setIsRevDataToFile(bool newIsRevDataToFile) override;

          // IPortBase interface
     public:
          void setConfigPanel(QWidget *widget) override;

     };
}

#endif // SERIALIMP_H
