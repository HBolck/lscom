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
    config.InputParam.SendInterval = "1000";//初始化定时发送的时间间隔ms
    config.InputParam.IsFileLoopSend = "0";//初始化循环发送文件为false
    config.InputParam.IsPLineSend = "1";//初始化逐行发送文件为true
    config.InputParam.FileSendLineInterval = "1000";
    QList<QString> list;
    for (int var = 0; var < 10; ++var) {
        list.append(QString("双击添加数据"));
    }
    config.InputParam.SendDataList = list;
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
