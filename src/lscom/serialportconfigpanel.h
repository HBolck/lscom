#ifndef SERIALPORTCONFIGPANEL_H
#define SERIALPORTCONFIGPANEL_H

#include <QWidget>
#include "Common/common.h"

namespace Ui
{
    class SerialPortConfigPanel;
}

class SerialPortConfigPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortConfigPanel(QWidget *parent = nullptr);

    void InitParam();
    SerialPortConfig GetSerialPortConfig();
    ~SerialPortConfigPanel();

private:
    Ui::SerialPortConfigPanel *ui;
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
        {"8", QSerialPort::Data8}};

    /**
     * @brief stopBitsMap
     */
    std::map<QString, QSerialPort::StopBits> stopBitsMap = {
        {"1", QSerialPort::OneStop},
        {"1.5", QSerialPort::OneAndHalfStop},
        {"2", QSerialPort::TwoStop}};

    /**
     * @brief parityMap
     */
    std::map<QString, QSerialPort::Parity> parityMap = {
        {"None", QSerialPort::NoParity},
        {"Odd", QSerialPort::EvenParity},
        {"Even", QSerialPort::OddParity}};
    QSerialPort::BaudRate mathBaudRate(const QString &str);
    QSerialPort::DataBits mathDataBits(const QString &str);
    QSerialPort::StopBits mathStopBits(const QString &str);
    QSerialPort::Parity mathParity(const QString &str);
    QStringList getSerialPorts();
    QStringList getSerialBundRates();
    QStringList getSerialDataBits();
    QStringList getSerialStopBits();
    QStringList getSerialParity();
};

#endif // SERIALPORTCONFIGPANEL_H
