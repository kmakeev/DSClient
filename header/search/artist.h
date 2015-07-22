#ifndef ARTIST
#define ARTIST

#include <QVariant>
#include <header/search/images.h>
#include <header/search/members.h>

class Artist
{
public:
    //Констуктор
    Artist (const QList<QString> &namevariations,
                       const QString &profiles,
                       const QString &releasesUrl,
                       const QString &resourceUrl,
                       const QString &uri,
                       const QList<QString> &urls,
                       const QString &data_quality,
                       const int &id,
                       const QList<Images> &images,        //класс для картинок
                       const QList<Members> &members);     //класс для участников (артистов)

    //Конструктор пустой

    Artist ();
    ~Artist ();



    //Функции для получения данных класса

    QList<QString> namevariations() const;

    QString profiles() const;
    QString releasesUrl() const;
    QString resourceUrl() const;
    QString uri() const;
    QList<QString> urls() const;
    QString data_quality() const;
    int id() const;
    QList<Images> images() const;
    QList<Members> members() const;



private:                    //Данные

    QList<QString> i_namevariations;
    QString i_profiles;
    QString i_releasesUrl;
    QString i_resourceUrl;
    QString i_uri;
    QList<QString> i_urls;
    QString i_data_quality;
    int i_id;
    QList<Images> i_Images;
    QList<Members> i_Members;


};

#endif // ARTIST

