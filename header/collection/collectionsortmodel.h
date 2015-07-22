#ifndef COLLECTIONSORTMODEL_H
#define COLLECTIONSORTMODEL_H
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QAbstractListModel>

class CollectionSortModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:

    CollectionSortModel (QObject *parent = 0);

    ~CollectionSortModel();

protected:
    int rowCount(const QModelIndex &parent) const;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
//    bool canFetchMore(const QModelIndex &parent) const;
//    void fetchMore(const QModelIndex &parent);

private:

 //   QAbstractItemModel * model;


};

#endif // COLLECTIONSORTMODEL_H
