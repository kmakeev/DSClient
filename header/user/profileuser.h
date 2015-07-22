#ifndef PROFILEUSER_H
#define PROFILEUSER_H
#include <QVariant>
#include <qdatetime.h>


class ProfileUser
{
public:
    ProfileUser(const QString &profile, const QString &wantlist_url, const int &rank, const int &num_pending, const int &id, const int &num_for_sale, const QString &home_page,
                const QString &collection_folders_url, const QString &username, const QString &collection_fields_url, const int &releases_contributed, const QDateTime &registred, const int &raiting_avg,
                const int &num_collection, const int &releases_raited, const int &num_lists, const QString &name, const int &num_wantlist, const QString &inventory_url, const QString avatar_url,const QString &uri, const QString &resource_url, const QString &email, const QString &location);

    ProfileUser();


    QString profile() const;
    QString wantlistUrl() const;
    int rank() const;
    int numPending() const;
    int id() const;
    int numForSale() const;
    QString homePage() const;
    QString collectionFoldersUrl() const;
    QString username() const;
    QString collectionFieldsUrl() const;
    int releasesContributed() const;
    QDateTime redistred() const;
    int raitingAvg() const;
    int numCollection() const;
    int ReleasesRaited() const;
    int numLists() const;
    QString name() const;
    int numWantlist() const;
    QString inventoryUrl() const;
    QString avatarUrl() const;
    QString uri() const;
    QString resourceUrl() const;
    QString email() const;
    QString location() const;



private:
    QString u_profile;
    QString u_wantlistUrl;
    int u_rank;
    int u_numPending;
    int u_id;
    int u_numForSale;
    QString u_homePage;
    QString u_collectionFoldersUrl;
    QString u_username;
    QString u_collectionFieldsUrl;
    int u_releasesContributed;
    QDateTime u_registred;
    int u_raitingAvg;
    int u_numCollection;
    int u_ReleasesRaited;
    int u_numLists;
    QString u_name;
    int u_numWantlist;
    QString u_inventoryUrl;
    QString u_avatarUrl;
    QString u_uri;
    QString u_resourceUrl;
    QString u_email;
    QString u_location;
};




#endif // PROFILEUSER_H
