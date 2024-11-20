#include "logservice.h"

LogService::LogService() {}

void LogService::setTextLog(QTextEdit *textEdit,const char* str)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTime = currentDateTime.toString("[yyyy-MM-dd hh:mm:ss]");
    textEdit->append(QString("<font color='gray' size='2'>%1 输出日志内容</font>").arg(dateTime));
    textEdit->append(QString("<font color='blue'>%1</font>").arg(str));
}
