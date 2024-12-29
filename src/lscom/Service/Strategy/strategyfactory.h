#ifndef STRATEGYFACTORY_H
#define STRATEGYFACTORY_H

#include "Port/PortBase.h"
#include "Service/logservice.h"

namespace strategy_factory
{

    /*
     * 这个工厂默认构建已知的协议实例
     * 通过指定的策略指向不同的实例，每个实例中的行为方法名和参数表相同，但是实现不同
     */

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
         * @brief 指向协议
         * @param protocol
         */
        void PointToPotocol(Protocol protocol);

        /**
         * @brief 协议的实现指针
         */
        lscom_port::IPortBase *PotocolImp;

        /**
         * @brief 初始化容器中协议实例的对象
         * @param widgets
         */
        void InitConfigPanel(std::map<Protocol, QWidget *> widgets);

        ~StrategyFactory();

    private:
        std::map<Protocol, lscom_port::IPortBase *> portImpCache;
        lscom_service::LogService *log;
        QTextEdit *textEdit;
    };
}

#endif // STRATEGYFACTORY_H
