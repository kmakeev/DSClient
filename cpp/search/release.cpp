#include <header/search/release.h>


///******************************************************************************************************************
Release::Release (const QString &title,
                  const int &id,
                  const QList<Artists> &artists,   //клас для списка артистов, участвовавших в записе релиза
                  const QString &data_quality,
                  const QString &thumb,
                  const Community &community,          //класс для коммунити, редактировавших информацию об релизе
                  const QList<Companies> &companies,               //класс для компаний участвовших в записи
                  const QString &country,
                  const QDateTime &date_added,
                  const QDateTime &date_changed,
                  const QString &estimated_weight,
                  const QList<Artists> &extraartists,          //класс для яэкстраартистов
                  const QString &format_quantity,
                  const QList<Formats> &formats,                 //класс для информации о формате
                  const QList<QString> &genres,
                  const QList<Identifiers> &identifiers,           //класс для идентификаторов релиза
                  const QList<Images> &images,                   //класс для картинок релиза
                  const QList<Companies> &labels,                   //класс для лейбла(ов) релиза
                  const int &master_id,
                  const QString &master_url,
                  const QString &notes,
                  const QString &released,
                  const QString &released_formatted,
                  const QString &resourceUrl,
                  const QList<QString> &series,                   //Пока не знаю, что это
                  const QString &status,
                  const QList<QString> &styles,
                  const QList<Tracklist> &tracklist,
                  const QString &uri,
                  const QList <Videos> &videos,
                  const int &year):m_title(title),
    m_id(id),
    m_artists(artists),
    m_data_quality(data_quality),
    m_thumb(thumb),
    m_community (community),
    m_companies(companies),
    m_country(country),
    m_date_added(date_added),
    m_date_changed(date_changed),
    m_estimated_weight(estimated_weight),
    m_extraartists(extraartists),
    m_format_quantity(format_quantity),
    m_formats(formats),
    m_genres(genres),
    m_identifiers(identifiers),
    m_images(images),
    m_labels(labels),
    m_master_id(master_id),
    m_master_url(master_url),
    m_notes(notes),
    m_released(released),
    m_released_formatted(released_formatted),
    m_resourceUrl(resourceUrl),
    m_series(series),
    m_status(status),
    m_styles(styles),
    m_tracklist(tracklist),
    m_uri(uri),
    m_videos(videos),
    m_year(year)

{

}

///******************************************************************************************************************
Release::Release()
{

}
///******************************************************************************************************************
Release::~Release()
{

}


///******************************************************************************************************************


QString Release::title() const
{
    return m_title;
}

///******************************************************************************************************************

int Release::id() const
{
    return m_id;
}

///******************************************************************************************************************
QList<Artists> Release::artists() const
{
    return m_artists;
}

///******************************************************************************************************************
QString Release::data_quality() const
{
    return m_data_quality;
}

///******************************************************************************************************************
QString Release::thumb() const
{
    return m_thumb;
}

///******************************************************************************************************************
Community Release::community() const
{
    return m_community;
}

///******************************************************************************************************************
QList<Companies> Release::companies() const
{
    return m_companies;
}

///******************************************************************************************************************
QString Release::country() const
{
    return m_country;
}

///******************************************************************************************************************

QDateTime Release::date_added() const
{
    return m_date_added;
}

///******************************************************************************************************************
QDateTime Release::date_changed() const
{
    return m_date_changed;
}

///******************************************************************************************************************
QString Release::estimated_weight() const
{
    return m_estimated_weight;
}

///******************************************************************************************************************
QList<Artists> Release::extraartists() const
{
    return m_extraartists;
}

///******************************************************************************************************************
QString Release::format_quantity() const
{
    return m_format_quantity;
}

///******************************************************************************************************************
QList<Formats> Release::formats() const
{
    return m_formats;
}

///******************************************************************************************************************
QList<QString> Release::genres() const
{
    return m_genres;
}

///******************************************************************************************************************
QList<Identifiers> Release::identifiers() const
{
    return m_identifiers;
}

///******************************************************************************************************************
QList<Images> Release::images()
{
    return m_images;
}
///******************************************************************************************************************

QList<Companies> Release::labels()
{
    return m_labels;
}

///******************************************************************************************************************
int Release::master_id() const
{
    return m_master_id;
}

///******************************************************************************************************************
QString Release::master_url() const
{
    return m_master_url;
}

///******************************************************************************************************************
QString Release::notes() const
{
    return m_notes;
}

///******************************************************************************************************************
QString Release::released() const
{
    return m_released;
}

///******************************************************************************************************************
QString Release::released_formatted() const
{
    return m_released_formatted;
}

///******************************************************************************************************************
QString Release::resourceUrl() const
{
    return m_resourceUrl;
}

///******************************************************************************************************************
QList<QString> Release::series() const
{
    return m_series;
}

///******************************************************************************************************************
QString Release::status() const
{
    return m_status;
}

///******************************************************************************************************************
QList<QString> Release::styles() const
{
    return m_styles;
}

///******************************************************************************************************************
QList<Tracklist> Release::tracklist() const
{
    return m_tracklist;
}

///******************************************************************************************************************
QString Release::uri() const
{
    return m_uri;
}

///******************************************************************************************************************
QList <Videos> Release::videos() const
{
    return m_videos;
}

///******************************************************************************************************************
int Release::year() const
{
    return m_year;
}

