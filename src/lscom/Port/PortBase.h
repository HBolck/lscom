#ifndef PORTBASE_H
#define PORTBASE_H

#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>

/**
 * @brief 端口类型
 */
enum PortType
{
    RTU,
    UDP
};

/**
 * @brief The Protocol enum
 */
enum Protocol
{
    // 串口
    SerialPort,
    // tcp服务端
    TcpServer,
    // tcp客户端
    TcpClient,
    Udp,
    Mqtt,
    RedisClient
};

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

namespace lscom_port
{

    /**
     * @brief 端口行为接口
     */
    class IPortBase : public QObject
    {
        Q_OBJECT

    public:
        /**
         * @brief 打开端口
         */
        virtual void OpenPort() = 0;
        /**
         * @brief 关闭端口
         */
        virtual void ClosePort() = 0;
        /**
         * @brief 获取连接状态
         * @return
         */
        virtual bool GetConnectStatus() = 0;
        /**
         * @brief 获取端口类型
         * @return
         */
        virtual PortType getProtType() const = 0;

        virtual void SendData(QByteArray data) = 0;
        IPortBase();
        virtual ~IPortBase() {};

    signals:
        /**
         * @brief 接收数据长度信号
         * @param data
         */
        void RevDataLengthSignal(long data);
        /**
         * @brief 发送数据长度信号
         * @param data
         */
        void SendDataLengthSignal(long data);

    public:
        PortType protType;
        /**
         * @brief 是否被配置过
         */
        bool _isConfiged;

        /**
         * @brief HEX显示
         */
        bool _isHexDisplay;
        virtual bool isHexDisplay() const = 0;
        virtual void setIsHexDisplay(bool newIsHexDisplay) = 0;

        /**
         * @brief HEX发送
         */
        bool _isHexSend;
        virtual bool isHexSend() const = 0;
        virtual void setIsHexSend(bool newIsHexSend) = 0;

        bool isRevDataToFile;
        virtual void setIsRevDataToFile(bool newIsRevDataToFile) = 0;

        // ******************** 开始：串口部分定义 ********************
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

        virtual QStringList getSerialPorts() = 0;
        virtual QStringList getSerialBundRates() = 0;
        virtual QStringList getSerialDataBits() = 0;
        virtual QStringList getSerialStopBits() = 0;
        virtual QStringList getSerialParity() = 0;
        virtual QSerialPort::BaudRate mathBaudRate(const QString &str) = 0;
        virtual QSerialPort::DataBits mathDataBits(const QString &str) = 0;
        virtual QSerialPort::StopBits mathStopBits(const QString &str) = 0;
        virtual QSerialPort::Parity mathParity(const QString &str) = 0;
        virtual void initSerialPortInstance(SerialPortConfig config) = 0;

        // ******************** 结束：特定区域的描述 ********************
    };

}

#endif // PORTBASE_H
