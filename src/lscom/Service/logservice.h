#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "qtextedit.h"
#include "qdatetime.h"

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
        void setTextLog(QTextEdit *textEdit, const char *str, LogType logType = Inner, LogLevel logLevel = Info);
    };
}
#endif // LOGSERVICE_H
