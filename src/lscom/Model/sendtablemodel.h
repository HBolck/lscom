#ifndef SENDTABLEMODEL_H
#define SENDTABLEMODEL_H

#include <QAbstractListModel>

class SendTableModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    SendTableModel(QObject *parent = nullptr) : QAbstractItemModel(parent) {}

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // SENDTABLEMODEL_H
