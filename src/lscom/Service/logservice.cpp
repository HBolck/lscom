#include "logservice.h"
#include "qdatetime.h"
lscom_service::LogService::LogService()
{
    this->fileExtension = ".log";
    this->fileDirPath = "log";
    this->file = new QFile();
}

lscom_service::LogService::~LogService()
{
    disrotyFile();
}

void lscom_service::LogService::setTextLog(QTextEdit *textEdit, const char *str, LogType logType, LogLevel logLevel)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTime = currentDateTime.toString("[yyyy-MM-dd hh:mm:ss]");
    QString slogType;
    QString slogLevel;
    QString logBody;
    switch (logType)
    {
    case Rev:
        slogType = "Rev收";
        break;
    case Send:
        slogType = "Send发";
        break;
    case Inner:
        slogType = "*";
        break;
    default:
        slogType = "*";
        break;
    }

    switch (logLevel)
    {
    case Info:
        slogLevel = "Info";
        logBody = QString("<font color='green'>%1</font>").arg(str);
        break;
    case Warning:
        slogLevel = "Send";
        logBody = QString("<font color='orange'>%1</font>").arg(str);
        break;
    case Error:
        slogLevel = "Error";
        logBody = QString("<font color='red'>%1</font>").arg(str);
        break;
    case Debug:
        slogLevel = "Debug";
        logBody = QString("<font color='gray'>%1</font>").arg(str);
        break;
    default:
        logBody = QString("<font color='gray' size='1'>%1</font>").arg(str);
        break;
    }
    textEdit->append(QString("<font color='gray' size='2'>%1 日志内容 %2</font>").arg(dateTime).arg(slogType));
    textEdit->append(logBody);
}

void lscom_service::LogService::writeLogToFile(const char *str, const char *groupName, LogLevel logLevel)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString fileName = currentDateTime.toString("yyyyMMddhh");
    QString dayPath = currentDateTime.toString("yyyyMMdd");
    QString currentPath = QCoreApplication::applicationDirPath();
    QString dirPath = currentPath + "/" + this->fileDirPath + "/" + groupName + "/" + dayPath;
    QString filePath = dirPath + "/" + fileName + this->fileExtension;
    createFolderIfNotExist(dirPath);   
    QString dateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    file->setFileName(filePath);
    QString logContent = "[" + this->getLogLevelStr(logLevel) + "]\r" + dateTime + ":\t" + "\r" + str;
    if (file->open(QIODevice::Append | QIODevice::Text | QIODevice::WriteOnly))
    {
        QTextStream out(file);
        out << logContent;
        file->close();
    }
}

/**
 * @brief 释放文件资源
 */
void lscom_service::LogService::disrotyFile()
{
    delete file;
}

/**
 * @brief 生成指定格式的时间串
 * @param format 时间格式
 * @param timeStr 时间字符串变量
 * @param size 字符串容量大小
 */
void lscom_service::LogService::generic_time_str(TimeFormat format, char *timeStr, size_t size)
{
    time_t rawtme;
    struct tm *timeinfo;
    time(&rawtme);
    timeinfo = localtime(&rawtme);
    switch (format)
    {
    case YYMMDDHHmmss:
        strftime(timeStr, size, "%Y-%m-%d %H:%M:%S", timeinfo);
        break;
    case YYMMDDHH:
        strftime(timeStr, size, "%Y-%m-%d %H", timeinfo);
        break;
    case YYMMDD:
        strftime(timeStr, size, "%Y-%m-%d", timeinfo);
        break;
    default:
        strftime(timeStr, size, "%Y-%m-%d %H:%M:%S", timeinfo);
        break;
    }
}

/**
 * @brief 生成指定时间的字符串内容
 * @param timeStr 时间字符串变量
 * @param size 字符串容量大小
 */
void lscom_service::LogService::generic_time_path(char *timeStr)
{
    time_t rawtme;
    struct tm *timeinfo;
    time(&rawtme);
    timeinfo = localtime(&rawtme);
    strftime(timeStr, 11, "%Y%m%d%H", timeinfo);
}

QString lscom_service::LogService::getLogLevelStr(LogLevel level)
{
    QString levelStr;
    // 拼接日志内容
    switch (level)
    {
    case Info:
        levelStr = "Info";
        break;
    case Warning:
        levelStr = "Warning";
        break;
    case Error:
        levelStr = "Error";
        break;
    case Debug:
        levelStr = "Debug";
        break;
    default:
        levelStr = "Info";
        break;
    }
    return levelStr;
}
