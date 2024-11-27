#ifndef PORTBASE_H
#define PORTBASE_H

#include <QCoreApplication>


/**
 * @brief 端口类型
 */
enum PortType
{
    RTU,
    TCP,
    UDP
};

namespace lscom_port
{

    /**
     * @brief 端口行为接口
     */
    class IPortBase
    {
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

    protected:
        PortType protType;
    };


}

#endif // PORTBASE_H
