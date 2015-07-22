#include "header/collection/collectionsortmodel.h"

#include <QSortFilterProxyModel>



CollectionSortModel::CollectionSortModel (QObject *parent) : QSortFilterProxyModel(parent)
{
    qDebug() << "CollectionSortModel constructor ";


}
///******************************************************************************************************************
CollectionSortModel::~CollectionSortModel()
{

}

///******************************************************************************************************************
bool CollectionSortModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
 //  QAbstractItemModel * model = sourceModel();
   qDebug() << "Filter source_row " << source_row;
 /*  if (source_row < 10){
       qDebug() << model->data(model->index(source_row,0,source_parent),Qt::UserRole +1);
        return true;
   } else return false;*/
   return true;

}

///******************************************************************************************************************
bool CollectionSortModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return true;
}

 int CollectionSortModel::rowCount(const QModelIndex &parent) const
 {
     QAbstractItemModel * model = sourceModel();
    qDebug() << "Filter count " << model->rowCount();;
    return model->rowCount();
 }
/*
bool CollectionSortModel::canFetchMore(const QModelIndex &parent) const
{
    return false;
}
///*******************************************************************************************

void CollectionSortModel::fetchMore(const QModelIndex &parent)
{
    if (!parent.isValid())
    {

        //      getData(pagesAtNextSearch);

    }
}
*/
