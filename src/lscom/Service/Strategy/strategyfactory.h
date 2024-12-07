#ifndef STRATEGYFACTORY_H
#define STRATEGYFACTORY_H

#include "Port/PortBase.h"
#include "Service/logservice.h"

namespace strategy_factory
{
    class StrategyFactory
    {
    public:
        StrategyFactory();
        StrategyFactory(lscom_service::LogService *log, QTextEdit *textEdit);
        /**
         * @brief 协议的实例
         * @param protocol
         * @return 实例的指针
         */
        lscom_port::IPortBase *PotocolInstance(Protocol protocol);
        /**
         * @brief 协议的实现指针
         */
        lscom_port::IPortBase *PotocolImp;
        ~StrategyFactory();

    private:
        std::map<Protocol, lscom_port::IPortBase *> portImpCache;
    };
}

#endif // STRATEGYFACTORY_H
