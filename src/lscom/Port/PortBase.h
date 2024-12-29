#ifndef PORTBASE_H
#define PORTBASE_H

#include "Common/common.h"
#include "serialportconfigpanel.h"

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

    protected:
        /**
         * @brief 串口配置面板
         */
        SerialPortConfigPanel *serialPanel;

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

        virtual void setConfigPanel(QWidget *widget) = 0;
    };

}

#endif // PORTBASE_H
