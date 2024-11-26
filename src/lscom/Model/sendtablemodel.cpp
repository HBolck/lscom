#include "sendtablemodel.h"

int SendTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())return 0;
    return 0;
}

QVariant SendTableModel::data(const QModelIndex &index, int role) const
{

}
