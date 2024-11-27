#include "configservice.h"

lscom_service::ConfigService::ConfigService()
{
}

lscom_service::ConfigService::~ConfigService()
{
}

/**
 * @brief 初始化配置文件
 */
Config lscom_service::ConfigService::InitConfigFile()
{
    Config config;
    config.InputParam.RevDataToFilePath = "Rev";
    config.InputParam.SendAreaData = GLOBAL_CODE_SOURCE_URL;
    config.InputParam.SendInterval = "1000";
    if (checkFileExist(GLOBAL_CONFIG_FILE_NAME) == false)
    {
        this->WriteConfigToFile(config);
    }
    else
    {
        QString fileContent = readFileContents(GLOBAL_CONFIG_FILE_NAME);
        if (fileContent.isEmpty())
        {
            this->WriteConfigToFile(config);
            return config;
        }
        else
        {
            bool flag = jsonToConfig(fileContent, config);
            if (flag == true)
                return config;
            else
            {
                this->WriteConfigToFile(config);
                return config;
            }

        }
    }
    return config;
}

void lscom_service::ConfigService::WriteConfigToFile(Config &config)
{
    auto json = configToJson(config);
    writeJsonToFile(GLOBAL_CONFIG_FILE_NAME, json);
}
