#ifndef MASTER
#define MASTER
#include <QVariant>
#include <QDate>
#include <header/search/images.h>
#include <header/search/artists.h>
#include <header/search/tracklist.h>
#include <header/search/videos.h>

class Master
{
public:
    //Констуктор
    Master (const QList<QString> &styles,
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
            const QString &data_quality);


    //Функции для получения данных класса

                QList<QString> styles() const;
                QList<QString> genres() const;
                QList <Videos> videos() const;
                QString title() const;
                int main_release() const;
                QString main_release_url() const;
                QList<Artists> artists() const;
                QString versions_url() const;
                int year() const;
                QList<Images> images() const;
                QString resource_url() const;
                QList<Tracklist> tracklist() const;
                int id() const;
                QString data_quality() const;

    Master();
    ~Master();


private:                    //Данные

                QList<QString> m_styles;
                QList<QString> m_genres;
                QList <Videos> m_videos;
                QString m_title;
                int m_main_release;
                QString m_main_release_url;
                QList<Artists> m_artists;
                QString m_versions_url;
                int m_year;
                QList<Images> m_images;
                QString m_resource_url;
                QList<Tracklist> m_tracklist;
                int m_id;
                QString m_data_quality;

};

#endif // MASTER

