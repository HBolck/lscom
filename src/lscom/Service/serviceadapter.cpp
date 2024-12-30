#include "serviceadapter.h"

lscom_service::ServiceAdapter::ServiceAdapter()
{
}

lscom_service::ServiceAdapter::ServiceAdapter(QTextEdit *textEdit)
{
    this->logService = new lscom_service::LogService();
    this->strategyFactory = new strategy_factory::StrategyFactory(this->logService, textEdit);
    this->configService = new lscom_service::ConfigService();
    this->fileService = new lscom_service::FileService();
}

lscom_service::ServiceAdapter::~ServiceAdapter()
{
    delete fileService;
    delete configService;
    delete strategyFactory;
    delete logService;
}
