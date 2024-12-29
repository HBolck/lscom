#include "strategyfactory.h"
#include "Service/serialImp.h"
strategy_factory::StrategyFactory::StrategyFactory()
{
}

/**
 * @brief 策略工厂
 * @param log
 * @param textEdit
 */
strategy_factory::StrategyFactory::StrategyFactory(lscom_service::LogService *log, QTextEdit *textEdit)
{
    this->log = log;
    this->textEdit = textEdit;
    this->portImpCache = {
        {SerialPort, new lscom_service::serialImp(log, textEdit)}};
}

/**
 * @brief 协议实例
 * @param protocol 协议类型
 * @return
 */
lscom_port::IPortBase *strategy_factory::StrategyFactory::PotocolInstance(Protocol protocol)
{
    if (portImpCache.find(protocol) != portImpCache.end())
    {
        this->PotocolImp = portImpCache[protocol];
    }
    else
    {
        this->PotocolImp = nullptr;
    }
    return this->PotocolImp;
}

/**
 * @brief 指向协议类型
 * @param protocol 协议类型
 */
void strategy_factory::StrategyFactory::PointToPotocol(Protocol protocol)
{
    this->PotocolInstance(protocol);
}

/**
 * @brief 初始化配置面板
 * @param widgets
 */
void strategy_factory::StrategyFactory::InitConfigPanel(std::map<Protocol, QWidget *> widgets)
{
    // 初始化策略组中对象的配置面板
    for (auto item : portImpCache)
    {
        auto type = item.first;
        auto flter = std::find_if(widgets.begin(), widgets.end(), [type](const std::pair<Protocol, QWidget *> loopItem)
                                  { return type == loopItem.first; });
        if (flter != widgets.end())
        {
            item.second->setConfigPanel(flter->second);
        }
        // auto it = widgets.find(item.first);
        // if (it!= widgets.end())
        // {
        //     item.second->setConfigPanel(it->second);
        // }
    }
}

/**
 * @brief 析构
 */
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
