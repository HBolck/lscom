#ifndef TCPCONFGPANEL_H
#define TCPCONFGPANEL_H

#include <QWidget>

namespace Ui {
class TcpConfgPanel;
}

class TcpConfgPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TcpConfgPanel(QWidget *parent = nullptr);
    ~TcpConfgPanel();

private:
    Ui::TcpConfgPanel *ui;
};

#endif // TCPCONFGPANEL_H
