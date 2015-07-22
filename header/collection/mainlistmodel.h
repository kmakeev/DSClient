#ifndef MAINLISTMODEL_H
#define MAINLISTMODEL_H
#include <QStringListModel>


class MainlistModel : public QStringListModel
{
public:
    explicit MainlistModel(const QStringList &lst, QObject *parent = 0);

    ~MainlistModel();

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role= Qt::DisplayRole) const;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE QStringList stringList() const;

private:
    QStringList mainLst;

};

#endif // MAINLISTMODEL_H
