#ifndef SERVICEADAPTER_H
#define SERVICEADAPTER_H

#include "Service/logservice.h"
#include "Service/configservice.h"
#include "Service/Strategy/strategyfactory.h"
#include "Service/fileservice.h"

namespace lscom_service
{

    class ServiceAdapter
    {
    public:
        ServiceAdapter();
        ServiceAdapter(QTextEdit *textEdit);
        strategy_factory::StrategyFactory *strategyFactory;
        lscom_service::LogService *logService;
        lscom_service::ConfigService *configService;
        lscom_service::FileService *fileService;

        ~ServiceAdapter();
    };
}
#endif // SERVICEADAPTER_H
