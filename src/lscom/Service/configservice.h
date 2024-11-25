#ifndef CONFIGSERVICE_H
#define CONFIGSERVICE_H

#include "Common/common.h"

namespace lscom_service
{
    /**
     * @brief 配置服务类
     */
    class ConfigService
    {
    public:
        ConfigService();
        ~ConfigService();

    public:
        Config InitConfigFile();
    };
}
#endif // CONFIGSERVICE_H
