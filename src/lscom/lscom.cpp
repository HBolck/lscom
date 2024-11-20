#include "lscom.h"
#include "ui_lscom.h"

lscom::lscom(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lscom)
{
    ui->setupUi(this);
}

lscom::~lscom()
{
    delete ui;
}
