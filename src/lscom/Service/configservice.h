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
        /**
         * @brief 初始化配置文件
         * @return
         */
        Config InitConfigFile();
        /**
         * @brief WriteConfigToFile
         * @param config
         */
        void WriteConfigToFile(Config &config);
    };
}
#endif // CONFIGSERVICE_H
