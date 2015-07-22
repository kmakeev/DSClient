#include <QVariant>
#include <header/search/label.h>
#include <header/search/images.h>
#include <header/search/sublabels.h>


Label::Label (const QString &profile,
              const QString &releasesUrl,
              const QString &name,
              const QString &contact_info,
              const QString &uri,
              const QList<Companies> &sublabels,               //Класс для сублейблов
              const QList<QString> &urls,
              const QList<Images> &images,
              const QString &resourceUrl,
              const QString &data_quality,
              const int &id):i_profile(profile), i_releasesUrl(releasesUrl), i_name(name), i_contact_info(contact_info), i_uri(uri), i_Sublabels(sublabels),
    i_urls(urls), i_Images(images), i_resourceUrl(resourceUrl), i_data_quality(data_quality), i_id(id)

{

}

///******************************************************************************************************************
Label::Label()
{

}

///******************************************************************************************************************
Label::~Label()
{

}

///******************************************************************************************************************
QString Label::profile() const
{
    return i_profile;
}

///******************************************************************************************************************
QString Label::releasesUrl() const
{
    return i_releasesUrl;
}


///******************************************************************************************************************
QString Label::name() const
{
    return i_name;
}

///******************************************************************************************************************
QString Label::contact_info() const
{
    return i_contact_info;
}

///******************************************************************************************************************
QString Label::uri() const
{
    return i_uri;
}


///******************************************************************************************************************
QList<Companies> Label::sublabels() const
{
    return i_Sublabels;
}

///******************************************************************************************************************
QList<QString> Label::urls() const
{
    return i_urls;
}

///******************************************************************************************************************
QList<Images> Label::images() const
{
    return i_Images;
}

///******************************************************************************************************************
QString Label::resourceUrl() const
{
    return i_resourceUrl;
}

///******************************************************************************************************************
QString Label::data_quality() const
{
    return i_data_quality;
}

///******************************************************************************************************************
int Label::id() const
{
    return i_id;
}
