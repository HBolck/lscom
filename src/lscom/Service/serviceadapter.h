#ifndef SERVICEADAPTER_H
#define SERVICEADAPTER_H

#include "Service/logservice.h"
#include "Service/serialImp.h"
#include "Service/configservice.h"
#include "Service/Strategy/strategyfactory.h"

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

        ~ServiceAdapter();
    };
}
#endif // SERVICEADAPTER_H
