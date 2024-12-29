#include "tcpconfgpanel.h"
#include "ui_tcpconfgpanel.h"

TcpConfgPanel::TcpConfgPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpConfgPanel)
{
    ui->setupUi(this);
}

TcpConfgPanel::~TcpConfgPanel()
{
    delete ui;
}
