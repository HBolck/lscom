#ifndef SERIALPORTCONFIGPANEL_H
#define SERIALPORTCONFIGPANEL_H

#include <QWidget>
#include "Service/serialImp.h"

namespace Ui {
class SerialPortConfigPanel;
}

class SerialPortConfigPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortConfigPanel(QWidget *parent = nullptr);
    ~SerialPortConfigPanel();
    void setSerialImp(lscom_service::serialImp *newSerialImp);
    SerialPortConfig GetSerialPortConfig();

private:
    Ui::SerialPortConfigPanel *ui;
    lscom_service::serialImp *serialImp;
    void initSerialPortConfig();
};

#endif // SERIALPORTCONFIGPANEL_H
