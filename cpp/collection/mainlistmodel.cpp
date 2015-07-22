#include "header/collection/mainlistmodel.h"

MainlistModel::MainlistModel(const QStringList &lst, QObject *parent):
    QStringListModel(parent), mainLst(lst)
{


}
///******************************************************************************************************************
QVariant MainlistModel::data(const QModelIndex &index, int role) const
{
//    QStringList mainLst = lst;

    if (index.row()<0 || index.row()>= mainLst.size())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return mainLst.at(index.row());
    }
    return QVariant();
}
///******************************************************************************************************************
int MainlistModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mainLst.count();

}

QStringList MainlistModel::stringList() const
{
    return mainLst;
}


///******************************************************************************************************************
MainlistModel::~MainlistModel()
{

}

