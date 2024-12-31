QT       += core gui
QT       += serialport
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Common/common.cpp \
    Delegate/qstylewithbuttondelegate.cpp \
    Port/PortBase.cpp \
    Service/Strategy/strategyfactory.cpp \
    Service/TcpService/tcpclient.cpp \
    Service/TcpService/tcpserver.cpp \
    Service/configservice.cpp \
    Service/fileservice.cpp \
    Service/logservice.cpp \
    Service/serialImp.cpp \
    Service/serviceadapter.cpp \
    main.cpp \
    lscom.cpp \
    serialportconfigpanel.cpp \
    tcpconfgpanel.cpp

HEADERS += \
    Common/common.h \
    Delegate/qstylewithbuttondelegate.h \
    Port/PortBase.h \
    Service/Strategy/strategyfactory.h \
    Service/TcpService/tcpclient.h \
    Service/TcpService/tcpserver.h \
    Service/configservice.h \
    Service/fileservice.h \
    Service/logservice.h \
    Service/serialImp.h \
    Service/serviceadapter.h \
    lscom.h \
    serialportconfigpanel.h \
    tcpconfgpanel.h

FORMS += \
    lscom.ui \
    serialportconfigpanel.ui \
    tcpconfgpanel.ui

TRANSLATIONS += \
    lscom_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    r_file.qrc
