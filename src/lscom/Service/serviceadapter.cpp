#include "serviceadapter.h"

lscom_service::ServiceAdapter::ServiceAdapter()
{
}

lscom_service::ServiceAdapter::ServiceAdapter(QTextEdit *textEdit)
{
    this->logService = new lscom_service::LogService();
    this->strategyFactory = new strategy_factory::StrategyFactory(this->logService, textEdit);
    // this->serialService = new lscom_service::serialImp(this->logService, textEdit);
    this->configService = new lscom_service::ConfigService();
}

lscom_service::ServiceAdapter::~ServiceAdapter()
{
    delete configService;
    // delete serialService;
    delete strategyFactory;
    delete logService;
}
