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
    Service/logservice.cpp \
    Service/serialImp.cpp \
    main.cpp \
    lscom.cpp

HEADERS += \
    Common/common.h \
    Service/logservice.h \
    Service/serialImp.h \
    lscom.h

FORMS += \
    lscom.ui

TRANSLATIONS += \
    lscom_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
