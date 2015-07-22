#include <QVariant>
#include <header/search/artist.h>



//Констуктор


Artist::Artist (const QList<QString> &namevariations,
                const QString &profiles,
                const QString &releasesUrl,
                const QString &resourceUrl,
                const QString &uri,
                const QList<QString> &urls,
                const QString &data_quality,
                const int &id,
                const QList<Images> &images,
                const QList<Members> &members):i_namevariations(namevariations),i_profiles(profiles),i_releasesUrl(releasesUrl), i_resourceUrl(resourceUrl),
    i_uri(uri),i_urls(urls), i_data_quality(data_quality), i_id(id),i_Images(images),i_Members(members)

{

}

///******************************************************************************************************************
Artist::Artist () //Конструктор для пустого класса без данных

{


}

///******************************************************************************************************************
Artist::~Artist () //

{


}

///******************************************************************************************************************
QList<QString> Artist::namevariations() const
{
    return i_namevariations;
}

///******************************************************************************************************************
QString Artist::profiles() const
{
    return i_profiles;
}

///******************************************************************************************************************
QString Artist::releasesUrl() const
{
    return i_releasesUrl;
}


///******************************************************************************************************************
QString Artist::resourceUrl() const
{
    return i_resourceUrl;
}


///******************************************************************************************************************
QString Artist::uri() const
{
    return i_uri;
}


///******************************************************************************************************************
QList<QString> Artist::urls() const
{
    return i_urls;
}


///******************************************************************************************************************
QString Artist::data_quality() const
{
    return i_data_quality;
}


///******************************************************************************************************************
int Artist::id() const
{
    return i_id;
}


///******************************************************************************************************************
QList<Images> Artist::images() const
{
    return i_Images;
}

///******************************************************************************************************************
QList<Members> Artist::members() const
{
    return i_Members;
}

