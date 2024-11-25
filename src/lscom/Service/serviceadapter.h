#ifndef SERVICEADAPTER_H
#define SERVICEADAPTER_H

#include "Service/logservice.h"
#include "Service/serialImp.h"

namespace lscom_service
{

    class ServiceAdapter
    {
    public:
        ServiceAdapter();
        ServiceAdapter(QTextEdit *textEdit);
        lscom_service::serialImp *serialService;
        lscom_service::LogService *logService;

        ~ServiceAdapter();
    };
}
#endif // SERVICEADAPTER_H
