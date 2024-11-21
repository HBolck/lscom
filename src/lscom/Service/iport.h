#include <iostream>
#include <windows.h>
#include <QMainWindow>
#include <QDebug>
#include <map>
#ifndef IPORT_H
#define IPORT_H

/**
 * @brief 端口类型
 */
enum PortType{
    Serial = 0x01,
    Net = 0x02
};

class IPort
{
public:
    /**
     * @brief getDescription
     * @return 描述内容
     */
    std::string getDescription();

    /**
     * @brief 端口类型
     */
    PortType portType;
};

#endif // IPORT_H
