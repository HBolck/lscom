#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "qtextedit.h"
#include "qdatetime.h"
class LogService
{
public:
    LogService();
    void setTextLog(QTextEdit *textEdit,const char* str);
};

#endif // LOGSERVICE_H
