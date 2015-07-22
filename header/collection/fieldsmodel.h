#ifndef FIELDSMODEL_H
#define FIELDSMODEL_H
#include <QAbstractListModel>
#include <QStringList>
#include <header\system\o1requestor.h>
#include <header\collection\fields.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>



class FieldsModel : public QAbstractListModel
{

    Q_OBJECT


    enum CollectionModelRoles {Name= Qt::UserRole + 1,id, Position, Type, Public, Lines, CountOptions, Options, isDropdown, Model};

public:


    explicit FieldsModel(QObject *parent = 0);

    Q_PROPERTY(bool isOffline READ isOffline NOTIFY isOfflineChanged)

    Q_INVOKABLE   int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    bool canFetchMore(const QModelIndex &parent) const;

    void fetchMore(const QModelIndex &parent);

    void getData(const int &i);

    bool readOffLineFields();

    void getFields();

    Q_INVOKABLE bool isOffline();

    Q_INVOKABLE void clear();

    Q_INVOKABLE void refresh();


signals:

    void isOfflineChanged();
    void fieldsChanged();

protected:

//    Fields oneFields;
    int timeOut; //Вынести в синглтон

    QHash<int, QByteArray> roleNames() const;

public: QList<Fields> m_Fields;                  //Список полей пользователя

};

#endif // FIELDSMODEL_H
