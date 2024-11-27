#include "qstylewithbuttondelegate.h"

QWidget *QStyleWithButtonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 1)
    { // 假设在第二列添加按钮
        QPushButton *button = new QPushButton("发送", parent);
        connect(button, &QPushButton::clicked, this, [=]()
                {
            QString context = (index.model()->data(index.sibling(index.row(), 0))).toString();
                    // 在这里处理按钮的点击事件
                    // qDebug() << "Button content " << context << " clicked.";
                    if(this->port != nullptr)
                    {
                        this->port->SendData(context.toUtf8());
                    } });
        return button;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void QStyleWithButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 1)
    { // 假设在第二列添加按钮
        QStyleOptionButton buttonOption;
        buttonOption.rect = option.rect;
        buttonOption.text = "发送";
        buttonOption.state = QStyle::State_Enabled;
        QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
