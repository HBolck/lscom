#include "strategyfactory.h"
#include "Service/serialImp.h"
strategy_factory::StrategyFactory::StrategyFactory()
{
}

strategy_factory::StrategyFactory::StrategyFactory(lscom_service::LogService *log, QTextEdit *textEdit)
{
    this->portImpCache = {
        {SerialPort, new lscom_service::serialImp(log, textEdit)}};
    this->PotocolImp = portImpCache[SerialPort];
}

lscom_port::IPortBase *strategy_factory::StrategyFactory::PotocolInstance(Protocol protocol)
{
    this->PotocolImp = portImpCache[protocol];
    return PotocolImp;
}

strategy_factory::StrategyFactory::~StrategyFactory()
{
    for (auto item : portImpCache)
    {
        if (item.second)
        {
            delete item.second;
        }
    }
}
