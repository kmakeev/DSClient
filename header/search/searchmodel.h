#ifndef SEARCHMODEL
#define SEARCHMODEL

#include <QAbstractListModel>
#include <QStringList>
#include <header\system\o1requestor.h>
#include <header\search\searchresult.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


const int pagesAtFirstSearch = 3;
const int pagesAtNextSearch = 1;


class SearchModel : public QAbstractListModel
{

    Q_OBJECT

    Q_PROPERTY(bool waitFirstSearch READ waitFirstSearch WRITE setWaitFirstSearch NOTIFY waitFirstSearchChanged)
 //   Q_PROPERTY(bool releases READ readReleases WRITE addReleases NOTIFY releasesChanged)


    //    Q_PROPERTY(SearchResult result READ result NOTIFY resultChanged)

//    Q_PROPERTY(bool itemWait READ itemWait WRITE setItemWait NOTIFY itemWaitChanged)


//    enum SearchModelRoles2 {OneSearchResult=Qt::UserRole+1};

    enum SearchModelRoles {isDummy= Qt::UserRole + 1,Type, isLoading, isArtist, isRelease, isMaster, isLabel,
        Title, Thumb, ResourseUrl, LabelShort, Format, Country, Year, Catno, Genre, Style,
        ReleaseNotes, ArtistUrls, ArtistNamevariations, ArtistProfiles,LabelName, LabelProfiles,LabelUrls,InWL,InCL};



public:

    explicit SearchModel(QObject *parent = 0);

    //   static QByteArray createQueryParams(const QList<O1RequestParameter> &params);

    Q_INVOKABLE void search(QString text);

    Q_INVOKABLE bool waitFirstSearch() const;

    Q_INVOKABLE void setWaitFirstSearch (const bool &a);

    Q_INVOKABLE void readReleases(const int &index);

    Q_INVOKABLE bool addReleasesInWantlist(const int &index);

    Q_INVOKABLE bool editReleasesInWantlist(const int &index, const int &rating);

    Q_INVOKABLE bool editReleasesInWantlist(const int &index, const QString &notes);

    Q_INVOKABLE bool addReleasesInCollection(const int &index);

    Q_INVOKABLE void setFilterToSearch (const QString &s);

    Q_INVOKABLE bool editReleasesInCollection(const int &index, const int &rating, const int &folderNumber);

    Q_INVOKABLE bool editFieldsInCollection(const int &index,  const int &idFieldsToEdit, const QString &valueFieldToEdit);

    Q_INVOKABLE void clear();

    Q_INVOKABLE   int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    bool canFetchMore(const QModelIndex &parent) const;

    void fetchMore(const QModelIndex &parent);

    void getData();

    void addSearchResult (const QJsonObject &o);

    QString jArrayToString(const QJsonArray &inputArray );

    QString fromjIterToString(const QJsonObject &o, const QString field);
    QString qlistToString(const QList<QString> & inpitList) const;

    bool getInfoForRelease (const int &index);

    bool getInfoForMaster (const int &index);

    bool getInfoForArtist (const int &index);

    bool getInfoForLabel (const int &index);






signals:
    //   void resultChanged();  //Сигнал для делегата об изменении свойства
    void waitFirstSearchChanged();
    void releasesChanged();
    void addReleasesToWantlist();
    void addReleasesToCollection();
    void editReleasesToCollection();
    void editReleasesToWantlist();



public slots:





protected:
    QHash<int, QByteArray> roleNames() const;



private:
    QList<SearchResult> m_SearchResult;       // Это список найденных записей
    SearchResult oneSearchResult;           // это одна  запись.

 //   Release r;


    QString searchBy;
    int timeOut;
    int itemsInResult;
    int pagesInResult;
    int currentPage;
    QString nextPageForSearh;
    QUrl url;
    bool iWaitFirstSearch;

//    QString m_wantResource;
//    QString m_collectionFolder;
//    QString m_userName;

    QString iFilterToSearch;



};
#endif // SEARCHMODEL

