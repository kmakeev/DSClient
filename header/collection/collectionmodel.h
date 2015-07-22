#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <header\system\o1requestor.h>
#include <header\search\searchresult.h>
#include <header\collection\collectionreleases.h>
#include <header\user\profileModel.h>
#include <header\collection\folders.h>
#include <header\collection\fields.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <header\collection\collectionsortmodel.h>


class CollectionModel: public QAbstractListModel
{

    Q_OBJECT

    enum CollectionModelRoles {Title= Qt::UserRole + 1,Year, Thumb, FormatShort, LabelShort, LabelName, Catno, ArtistName, Rating, Folder, Field1, Field2, Field3};


public:

   explicit CollectionModel(QObject *parent = 0);

    Q_PROPERTY(bool isNotEmpty READ isNotEmpty NOTIFY isNotEmptyChanged)                          //Признак того, коллекция не пустая

    Q_PROPERTY(bool waitReadCollection READ waitReadCollection WRITE setWaitReadCollection NOTIFY waitReadCollectionChanged) //Свойство для тупилки при чтении коллекции

    Q_PROPERTY(bool isOffline READ isOffline NOTIFY isOfflineChanged)

 //   Q_PROPERTY(int progressValue READ progressValue NOTIFY progress)

 //   Q_PROPERTY (proxy READ proxy)

    //   Q_PROPERTY(int folderNameToFilter READ folderNameToFilter WRITE setFolderNameToFilter NOTIFY folderNameToFilterChanged)

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE bool isNotEmpty();

    Q_INVOKABLE void refresh();

    Q_INVOKABLE bool waitReadCollection() const;

    Q_INVOKABLE void setWaitReadCollection(const bool &a);

    Q_INVOKABLE int folderCount();

    Q_INVOKABLE int fieldCount();

    Q_INVOKABLE QString folderName (const int &i);

 //   Q_INVOKABLE QString fieldName (const int &i);

    Q_INVOKABLE void setFolderFilter (const int &i);

//    Q_INVOKABLE void setNumMediaField(const int &i);

//    Q_INVOKABLE void setNumSleeveField(const int &i);

    Q_INVOKABLE int getCountOptionsOfField(const int &i);

    Q_INVOKABLE QString getOptionsInField(const int &i,const int &n);

    Q_INVOKABLE int folderId (const int &i);

 //   Q_INVOKABLE int fieldsId (const int &i);

 //   Q_INVOKABLE int idForMediaCondition();

 //   Q_INVOKABLE  int idForSleeveCondition();

     Q_INVOKABLE bool isOffline();

     Q_INVOKABLE void clear();

//     Q_INVOKABLE QVariant proxy();

     Q_INVOKABLE void refreshFilter();

     Q_INVOKABLE float progressValue();


  //   Q_INVOKABLE void search();




   bool canFetchMore(const QModelIndex &parent) const;

   void fetchMore(const QModelIndex &parent);

   void getData(const int &i);

   void getReleasesInCollection();
   void getFoldersInCollection();
   void addResult (const QJsonObject &o);

   void getFilds();

   QString qlistToString(const QList<QString> & inpitList) const;

   QString nameOfFolder(const int & id) const;

   QString nameOfField(const int & id) const;

   QString labelNameToString(const QList<Companies> &companies) const;
   QString labelCatnoToString(const QList<Companies> &companies) const;

   bool readOffLineCollection();
   bool readOffLineFolder();



 //  Q_INVOKABLE bool getInstance (const int &index);
   //Сортировка

   Q_INVOKABLE void sortBy (const QString &param);
   static bool lessThanTitle(const CollectionReleases &s1, const CollectionReleases &s2);
   static bool lessThanArtist(const CollectionReleases &s1, const CollectionReleases &s2);
   static bool lessThanRating(const CollectionReleases &s1, const CollectionReleases &s2);
   static bool lessThanFormat(const CollectionReleases &s1, const CollectionReleases &s2);
   static bool lessThanLabel(const CollectionReleases &s1, const CollectionReleases &s2);
   static bool lessThanYear(const CollectionReleases &s1, const CollectionReleases &s2);
   static bool lessThanCatalog(const CollectionReleases &s1, const CollectionReleases &s2);


   //Поиск
   Q_INVOKABLE void search (const QString &param);
//   void searchNotes(const QString & param);
   void searchOtcher(const QString & param);
   bool searchCatno(const QString & param);
   bool checkInList(const QList<CollectionReleases>::const_iterator i);







protected:
    QHash<int, QByteArray> roleNames() const;

signals:
    void isNotEmptyChanged();
    void waitReadCollectionChanged();
    void folderRead();
    void isOfflineChanged();
    void progress();

private:
    //   int rowFolders;
//    int rowReleasesInCollection;

    QList<Folders> m_Folders;
    QList<Fields> m_Fields;

  //  CollectionSortModel m_sortFilterProxyModel;

//    QSortFilterProxyModel m_sortFilterProxyModel;


    QList<CollectionReleases> m_CollectionResult;       // Это список найденных записей в коллекции
    QList<CollectionReleases> f_CollectionResult;       // Это список записей в коллекции после установки фильра/поиска/сортировки

    CollectionReleases oneCollectionResult;
    int timeOut;

    int itemsInResult;
    int pagesInResult;
    int currentPage;
    QString nextPageForSearh;
    QUrl url;
 //   QString m_userResource;
    bool m_isNotEmpty;

    bool iwaitReadCollection;

    float progressValue_;

 //   int ifolderALLIdToFilter;
 //   int ifolderIdToFilter;
 //   int iNumMediaField;
 //   int iNumSleeveField;


};





#endif // COLLECTIONMODEL_H
