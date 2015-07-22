#include<header/search/master.h>

Master::Master (const QList<QString> &styles,
                const QList<QString> &genres,
                const QList <Videos> &videos,
                const QString &title,
                const int &main_release,
                const QString &main_release_url,
                const QList<Artists> &artists,   //клас для списка артистов, участвовавших в записе релиза
                const QString &versions_url,
                const int &year,
                const QList<Images> &images,                   //класс для картинок релиза
                const QString &resource_url,
                const QList<Tracklist> &tracklist,
                const int &id,
                const QString &data_quality):m_styles(styles), m_genres(genres), m_videos(videos), m_title(title), m_main_release(main_release),m_main_release_url(main_release_url),
    m_artists(artists), m_versions_url(versions_url), m_year(year), m_images(images),
    m_resource_url(resource_url), m_tracklist(tracklist),m_id(id),m_data_quality(data_quality)

{

}

///******************************************************************************************************************
Master::Master()
{

}

///******************************************************************************************************************
Master::~Master()
{

}

///******************************************************************************************************************

QList<QString> Master::styles() const
{
    return m_styles;
}

///******************************************************************************************************************

QList<QString> Master::genres() const
{
    return m_genres;
}

///******************************************************************************************************************

QList <Videos> Master::videos() const
{
    return m_videos;
}

///******************************************************************************************************************

QString Master::title() const
{
    return m_title;
}

///******************************************************************************************************************

int Master::main_release() const
{
    return m_main_release;
}

///******************************************************************************************************************

QString Master::main_release_url() const
{
    return m_main_release_url;
}

///******************************************************************************************************************

QList<Artists> Master::artists() const
{
    return m_artists;
}

///******************************************************************************************************************

QString Master::versions_url() const
{
    return m_versions_url;
}

///******************************************************************************************************************

int Master::year() const
{
    return m_year;
}

///******************************************************************************************************************

QList<Images> Master::images() const
{
    return m_images;
}

///******************************************************************************************************************

QString Master::resource_url() const
{
    return m_resource_url;
}

///******************************************************************************************************************

QList<Tracklist> Master::tracklist() const
{
    return m_tracklist;
}

///******************************************************************************************************************

int Master::id() const
{
    return m_id;
}

///******************************************************************************************************************

QString Master::data_quality() const
{
    return m_data_quality;
}
