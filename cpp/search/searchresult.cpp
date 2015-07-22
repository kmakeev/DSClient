#include <header/search/searchresult.h>
/*
SearchResult::SearchResult(const bool isDummy,
             const QString &type,
             const bool isLoading,
             const bool isArtist,
             const bool isRelease,
             const bool isMaster,
             const bool isLabel,
             const Artist &artist,
             const Release &release,
             const Master &master,
             const Label &label,
             const QString &title,
             const QString &thumb,
             const QString &resourceUrl,
             const QString &labelshort,
             const QString &format,
             const QString &country,
             const QString &year,
             const QString &catno,
             const QString &genre,
             const QString &style):a_isDummy(isDummy), a_type(type), a_isLoading(isLoading), a_isArtist(isArtist),a_isRelease(isRelease),a_isMaster(isMaster),a_isLabel(isLabel),
                                   a_artist(artist), a_release(release), a_master(master), a_label(label),
                                   a_title(title), a_thumb(thumb),a_resourceUrl(resourceUrl),a_labelshort(labelshort),
                                   a_format(format),a_country(country),a_year(year),a_catno(catno), a_genre(genre),a_style(style)
{


}*/
///******************************************************************************************************************
///

SearchResult::SearchResult(const bool isDummy,
             const QString &type,
             const bool isLoading,
             const bool isArtist,
             const bool isRelease,
             const bool isMaster,
             const bool isLabel,
             const QString &title,
             const QString &thumb,
             const QString &resourceUrl,
             const QString &labelshort,
             const QString &format,
             const QString &country,
             const QString &year,
             const QString &catno,
             const QString &genre,
             const QString &style):a_isDummy(isDummy), a_type(type), a_isLoading(isLoading), a_isArtist(isArtist),a_isRelease(isRelease),a_isMaster(isMaster),a_isLabel(isLabel),
                                   a_title(title), a_thumb(thumb),a_resourceUrl(resourceUrl),a_labelshort(labelshort),
                                   a_format(format),a_country(country),a_year(year),a_catno(catno), a_genre(genre),a_style(style)
{
   a_isInWl = false;              //пока так
   a_isInCl = false;

}

/*
SearchResult::SearchResult(const bool isDummy,
             const QString &type,
             const bool isLoading,
             const bool isArtist,
             const bool isRelease,
             const bool isMaster,
             const bool isLabel,
             const QString &title,
             const QString &thumb,
             const QString &resourceUrl,
             const QString &labelshort,
             const QString &format,
             const QString &country,
             const QString &year,
             const QString &catno,
             const QString &genre,
             const QString &style,
             const bool &isInWl,
             const bool &isInCl):a_isDummy(isDummy), a_type(type), a_isLoading(isLoading), a_isArtist(isArtist),a_isRelease(isRelease),a_isMaster(isMaster),a_isLabel(isLabel),
                                   a_title(title), a_thumb(thumb),a_resourceUrl(resourceUrl),a_labelshort(labelshort),
                                   a_format(format),a_country(country),a_year(year),a_catno(catno), a_genre(genre),a_style(style),a_isInWl(isInWl), a_isInCl(isInCl)
{


}
*/
///******************************************************************************************************************
SearchResult::SearchResult(const bool isDummy):a_isDummy(isDummy)
         /*    const bool isLoading,
             const bool isArtist,
             const bool isRelease,
             const bool isMaster,
             const bool isLabel): a_isDummy(isDummy), a_isLoading(isLoading), a_isArtist(isArtist),a_isRelease(isRelease),a_isMaster(isMaster),a_isLabel(isLabel)
*/
{

}

///******************************************************************************************************************

SearchResult::SearchResult()
{

}
///******************************************************************************************************************
SearchResult::~SearchResult()
{

}


///******************************************************************************************************************

bool SearchResult::isDummy() const
{
    return a_isDummy;
}
///******************************************************************************************************************

QString SearchResult::type() const
{
    return a_type;
}
///******************************************************************************************************************

bool SearchResult::isLoading() const
{
    return a_isLoading;
}
///******************************************************************************************************************

bool SearchResult::isArtist() const
{
    return a_isArtist;
}
///******************************************************************************************************************

bool SearchResult::isRelease() const
{
    return a_isRelease;
}
///******************************************************************************************************************

bool SearchResult::isMaster() const
{
    return a_isMaster;
}
///******************************************************************************************************************

bool SearchResult::isLabel() const
{
    return a_isLabel;
}
///******************************************************************************************************************

Artist SearchResult::artist() const
{
    return a_artist;
}
///******************************************************************************************************************

Release SearchResult::release() const
{
    return a_release;
}
///******************************************************************************************************************

Master SearchResult::master() const
{
    return a_master;
}
///******************************************************************************************************************

Label SearchResult::label() const
{
    return a_label;
}
///******************************************************************************************************************
QString SearchResult::title() const
{
    return a_title;
}

///******************************************************************************************************************
QString SearchResult::thumb() const
{
    return a_thumb;
}

///******************************************************************************************************************
QString SearchResult::resourceUrl() const
{
    return a_resourceUrl;
}

///******************************************************************************************************************
QString SearchResult::labelshort() const
{
    return a_labelshort;
}

///******************************************************************************************************************
QString SearchResult::format() const
{
    return a_format;
}

///******************************************************************************************************************
QString SearchResult::country() const
{
    return a_country;
}

///******************************************************************************************************************
QString SearchResult::year() const
{
    return a_year;
}
///******************************************************************************************************************
QString SearchResult::catno() const
{
    return a_catno;
}
///******************************************************************************************************************
QString SearchResult::genre() const
{
    return a_genre;
}
///******************************************************************************************************************
QString SearchResult::style() const
{
    return a_style;
}

///******************************************************************************************************************
void SearchResult::setRelease(const Release &r)
{
    a_release = r;
}
///******************************************************************************************************************
void SearchResult::setMaster(const Master &r)
{
    a_master = r;
}
/// *****************************************************************************************
void SearchResult::setLabel(const Label &r)
{
    a_label = r;
}
/// *****************************************************************************************
void SearchResult::setArtist(const Artist &r)
{
    a_artist = r;
}
/// *****************************************************************************************

void SearchResult::setIsLoading (const bool &a)
{
   a_isLoading = a;
}

///******************************************************************************************************************
bool SearchResult::isInWl() const
{
  return a_isInWl;
}
///******************************************************************************************************************
bool SearchResult::isInCl() const
{
    return a_isInCl;
}
///******************************************************************************************************************
QString SearchResult::resurceUrlInCollection() const
{
    return a_resourceUrlInCollection;
}

///******************************************************************************************************************
void SearchResult::setResourceUrlInCollection(const QString &a)
{
    a_resourceUrlInCollection = a;
}

///******************************************************************************************************************
int SearchResult::instanceInCollection() const
{
    return a_instanceInCollection;
}

///******************************************************************************************************************
void SearchResult::setInstanceInCollection(const int &a)
{
    a_instanceInCollection = a;
}

///******************************************************************************************************************
void SearchResult::setIsInWl(const bool &a)
{
    a_isInWl = a;
}

///******************************************************************************************************************
void SearchResult::setIsInCl(const bool &a)
{
   a_isInCl = a;
}
