#ifndef PORTBASE_H
#define PORTBASE_H


#include "Service/logservice.h"
#endif // PORTBASE_H

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

    };

}
