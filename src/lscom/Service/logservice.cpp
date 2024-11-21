#include "logservice.h"

LogService::LogService() {}

void LogService::setTextLog(QTextEdit *textEdit,const char* str,LogType logType,LogLevel logLevel)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTime = currentDateTime.toString("[yyyy-MM-dd hh:mm:ss]");



    QString slogType;
    QString slogLevel;
    QString logBody;
    switch (logType) {
    case Rev:
        slogType = "Rev收<<";
        break;
    case Send:
        slogType = "Send发>>";
        break;
    case Inner:
        slogType = "*";
        break;
    default:
        slogType = "*";
        break;
    }

    switch (logLevel) {
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
