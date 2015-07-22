#include "header/user/profileuser.h"
#include <QDebug>

ProfileUser::ProfileUser(const QString &profile, const QString &wantlist_url, const int &rank, const int &num_pending, const int &id, const int &num_for_sale, const QString &home_page,
                         const QString &collection_folders_url, const QString &username, const QString &collection_fields_url, const int &releases_contributed, const QDateTime &redistred, const int &raiting_avg,
                         const int &num_collection, const int &releases_raited, const int &num_lists, const QString &name, const int &num_wantlist, const QString &inventory_url, const QString avatar_url, const QString &uri, const QString &resource_url, const QString &email, const QString &location):
                         u_profile(profile), u_wantlistUrl(wantlist_url), u_rank(rank), u_numPending(num_pending), u_id(id),u_numForSale(num_for_sale), u_homePage(home_page),
                         u_collectionFoldersUrl(collection_folders_url), u_username(username), u_collectionFieldsUrl(collection_fields_url), u_releasesContributed(releases_contributed), u_registred(redistred), u_raitingAvg(raiting_avg),
                         u_numCollection(num_collection), u_ReleasesRaited(releases_raited), u_numLists(num_lists), u_name(name), u_numWantlist(num_wantlist),u_inventoryUrl(inventory_url),u_avatarUrl(avatar_url), u_uri(uri),u_resourceUrl(resource_url),u_email(email), u_location(location)
{

 qDebug() << "ProfileUser constructor ";

}
///******************************************************************************************************************

ProfileUser::ProfileUser(){

}
///******************************************************************************************************************
QString ProfileUser::profile() const
{
    return u_profile;
}
///******************************************************************************************************************
QString ProfileUser::wantlistUrl() const
{
    return u_wantlistUrl;
}
///******************************************************************************************************************
int ProfileUser::rank() const
{
    return u_rank;
}
///******************************************************************************************************************
int ProfileUser::numPending() const
{
    return u_numPending;
}
///******************************************************************************************************************
int ProfileUser::id() const
{
    return u_id;
}
///******************************************************************************************************************
int ProfileUser::numForSale() const
{
    return u_numForSale;
}
///******************************************************************************************************************
QString ProfileUser::homePage() const
{
    return u_homePage;
}
///******************************************************************************************************************
QString ProfileUser::collectionFoldersUrl() const
{
    return u_collectionFoldersUrl;
}
///******************************************************************************************************************
QString ProfileUser::username() const
{
    return u_username;
}
///******************************************************************************************************************
QString ProfileUser::collectionFieldsUrl() const
{
    return u_collectionFieldsUrl;
}
///******************************************************************************************************************
int ProfileUser::releasesContributed() const
{
    return u_releasesContributed;
}
///******************************************************************************************************************
QDateTime ProfileUser::redistred() const
{
    return u_registred;
}
///******************************************************************************************************************
int ProfileUser::raitingAvg() const
{
    return u_raitingAvg;
}
///******************************************************************************************************************
int ProfileUser::numCollection() const
{
    return u_numCollection;
}
///******************************************************************************************************************
int ProfileUser::ReleasesRaited() const
{
    return u_ReleasesRaited;
}
///******************************************************************************************************************
int ProfileUser::numLists() const
{
    return u_numLists;
}
///******************************************************************************************************************
QString ProfileUser::name() const
{
    return u_name;
}

int ProfileUser::numWantlist() const
{
    return u_numWantlist;
}
///******************************************************************************************************************
QString ProfileUser::inventoryUrl() const
{
    return u_inventoryUrl;
}
///******************************************************************************************************************
QString ProfileUser::avatarUrl() const
{
    return u_avatarUrl;
}
///******************************************************************************************************************
QString ProfileUser::uri() const
{
    return u_uri;
}
///******************************************************************************************************************
QString ProfileUser::resourceUrl() const
{
    return u_resourceUrl;
}
///******************************************************************************************************************
QString ProfileUser::email() const
{
    return u_email;
}
///******************************************************************************************************************
QString ProfileUser::location() const
{
    return u_location;
}
