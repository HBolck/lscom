#ifndef QSTYLEWITHBUTTONDELEGATE_H
#define QSTYLEWITHBUTTONDELEGATE_H

#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QPushButton>
#include "Port/PortBase.h"

class QStyleWithButtonDelegate : public QStyledItemDelegate
{

public:
    lscom_port::IPortBase *port;

public:
    QStyleWithButtonDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {};

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;




};

#endif // QSTYLEWITHBUTTONDELEGATE_H
