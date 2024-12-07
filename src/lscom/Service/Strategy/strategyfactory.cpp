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

void strategy_factory::StrategyFactory::InitConfigPanel(std::map<Protocol,QWidget*> widgets)
{
    //初始化策略组中对象的配置面板
    for (auto item : portImpCache)
    {
        auto type = item.first;
        auto flter = std::find_if(widgets.begin(),widgets.end(),[type](const std::pair<Protocol,QWidget*> loopItem){
            return type == loopItem.first;
        });
        if(flter != widgets.end()){
            item.second->setConfigPanel(flter->second);
        }
        // auto it = widgets.find(item.first);
        // if (it!= widgets.end())
        // {
        //     item.second->setConfigPanel(it->second);
        // }
    }
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
