#ifndef RELEASE
#define RELEASE

#include <QVariant>
#include <QDate>
#include <header/search/images.h>
#include <header/search/members.h>
#include <header/search/artists.h>
#include <header/search/community.h>
#include <header/search/companies.h>
#include <header/search/formats.h>
#include <header/search/identifiers.h>
#include <header/search/tracklist.h>
#include <header/search/videos.h>

class Release
{
public:
    //Констуктор
    Release (const QString &title,
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
                       const int &year);

   Release();                   //пустой контруктор
   ~Release();

    //Функции для получения данных класса

         QString title() const;
         int id() const;
         QList<Artists> artists() const;
         QString data_quality() const;
         QString thumb() const;
         Community community() const;
         QList<Companies> companies() const;
         QString country() const;
         QDateTime date_added() const;
         QDateTime date_changed() const;
         QString estimated_weight() const;
         QList<Artists> extraartists() const;
         QString format_quantity() const;
         QList<Formats> formats() const;
         QList<QString> genres() const;
         QList<Identifiers> identifiers() const;
         QList<Images> images();
         QList<Companies> labels();
         int master_id() const;
         QString master_url() const;
         QString notes() const;
         QString released() const;
         QString released_formatted() const;
         QString resourceUrl() const;
         QList<QString> series() const;
         QString status() const;
         QList<QString> styles() const;
         QList<Tracklist> tracklist() const;
         QString uri() const;
         QList <Videos> videos() const;
         int year() const;








private:                    //Данные

         QString m_title;
         int m_id;
         QList<Artists> m_artists;
         QString m_data_quality;
         QString m_thumb;
         Community m_community;
         QList<Companies> m_companies;
         QString m_country;
         QDateTime m_date_added;
         QDateTime m_date_changed;
         QString m_estimated_weight;
         QList<Artists> m_extraartists;
         QString m_format_quantity;
         QList<Formats> m_formats;
         QList<QString> m_genres;
         QList<Identifiers> m_identifiers;
         QList<Images> m_images;
         QList<Companies> m_labels;
         int m_master_id;
         QString m_master_url;
         QString m_notes;
         QString m_released;
         QString m_released_formatted;
         QString m_resourceUrl;
         QList<QString> m_series;
         QString m_status;
         QList<QString> m_styles;
         QList<Tracklist> m_tracklist;
         QString m_uri;
         QList <Videos> m_videos;
         int m_year;


};




#endif // RELEASE

