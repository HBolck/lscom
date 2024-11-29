#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "qtextedit.h"
#include "Common/common.h"

/**
 * @brief 日志等级枚举
 */
enum LogLevel
{
    Info,
    Warning,
    Error,
    Debug
};

/**
 * @brief 日志类型枚举
 */
enum LogType
{
    Rev,
    Send,
    // 内部类型
    Inner
};

namespace lscom_service
{

    class LogService
    {
    public:
        LogService();
        ~LogService();
        void setTextLog(QTextEdit *textEdit, const char *str, LogType logType = Inner, LogLevel logLevel = Info);

        /**
         * @brief writeLogToFile
         * @param str
         * @param logLevel
         */
        void writeLogToFile(const char *str, const char *groupName, LogLevel logLevel = Info);

    private:
        /**
         * @brief 文件对象
         */
        QFile* file;
        /**
         * @brief 文件路径
         */
        QString fileDirPath;
        /**
         * @brief 文件扩展名
         */
        QString fileExtension;

    private:
        /**
         * @brief 释放文件资源
         */
        void disrotyFile();

        /**
         * @brief 生成指定格式的时间串
         * @param format 时间格式
         * @param timeStr 时间字符串变量
         * @param size 字符串容量大小
         */
        void generic_time_str(TimeFormat format, char *timeStr, size_t size);

        /**
         * @brief 生成指定时间的字符串内容
         * @param timeStr 时间字符串变量
         * @param size 字符串容量大小
         */
        void generic_time_path(char* timeStr);

        QString getLogLevelStr(LogLevel level);
    };
}

#endif // LOGSERVICE_H
