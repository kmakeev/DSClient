#ifndef WantlistModel_H
#define WantlistModel_H
#include <QAbstractListModel>
#include <QStringList>
#include <QUrl>
#include <header\system\o1requestor.h>
#include <header\user\profileModel.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <header/wantlist/wants.h>


class WantlistModel : public QAbstractListModel
{
    Q_OBJECT

    enum WantlistModelRoles {Title= Qt::UserRole + 1,Year, Thumb, FormatShort, LabelShort, LabelName, Catno, ArtistName, Rating};


public:
    explicit WantlistModel(QObject *parent = 0);

    ~WantlistModel();

    Q_PROPERTY(bool waitReadWantlist READ waitReadWantlist WRITE setWaitReadWantlist NOTIFY waitReadWantlistChanged) //Свойство для тупилки при чтении wantlist

    Q_PROPERTY(bool isOffline READ isOffline NOTIFY isOfflineChanged)

    Q_INVOKABLE   int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);

    QString qlistToString(const QList<QString> & inputList) const;
    Q_INVOKABLE void getReleasesInWantList();

    Q_INVOKABLE bool waitReadWantlist() const;

    Q_INVOKABLE void setWaitReadWantlist (const bool &a);

    void addResult (const QJsonObject &o);

    QString labelNameToString(const QList<Companies> &companies) const;
    QString labelCatnoToString(const QList<Companies> &companies) const;

    Q_INVOKABLE bool deleteReleaseFromWantlist(const int &index);
    Q_INVOKABLE void refresh();

    Q_INVOKABLE bool isOffline();

   bool readOffLineWantList();

   Q_INVOKABLE void clear();

signals:

    void waitReadWantlistChanged();
    void isOfflineChanged();


protected:

    QHash<int, QByteArray> roleNames() const;



private:

    int rowReleasesInWant;            //Количество записей в wantлисте

 //   QString m_wantResource;           //Путь к wantлисту пользователя

    QList<Wants> m_WantsResult;       // Это список найденных записей
    Wants oneWantsResult;
    int timeOut;
    int itemsInResult;
    int pagesInResult;
    int currentPage;
    QString nextPageForSearh;
    QUrl url;

    bool iWaitReadWantlist;





};
#endif // WantlistModel_H
