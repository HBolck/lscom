#ifndef SERVICEADAPTER_H
#define SERVICEADAPTER_H

#include "Service/logservice.h"
#include "Service/serialImp.h"
#include "Service/configservice.h"


namespace lscom_service
{

    class ServiceAdapter
    {
    public:
        ServiceAdapter();
        ServiceAdapter(QTextEdit *textEdit);
        lscom_service::serialImp *serialService;
        lscom_service::LogService *logService;
        lscom_service::ConfigService *configService;

        ~ServiceAdapter();
    };
}
#endif // SERVICEADAPTER_H
