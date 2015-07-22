#ifndef LABEL
#define LABEL

#include <QVariant>
#include <header/search/images.h>
#include <header/search/companies.h>

class Label
{
public:
    //Констуктор
    Label (const QString &profile,
                       const QString &releasesUrl,
                       const QString &name,
                       const QString &contact_info,
                       const QString &uri,
                       const QList<Companies> &sublabels,               //Класс для сублейблов
                       const QList<QString> &urls,
                       const QList<Images> &images,
                       const QString &resourceUrl,
                       const QString &data_quality,
                       const int &id);




    Label();

    ~Label();

    //Функции для получения данных класса

    QString profile() const;
    QString releasesUrl() const;
    QString name() const;
    QString contact_info() const;
    QString uri() const;
    QList<Companies> sublabels() const;
    QList<QString> urls() const;
    QList<Images> images() const;
    QString resourceUrl() const;
    QString data_quality() const;
    int id() const;




private:                    //Данные

    QString i_profile;
    QString i_releasesUrl;
    QString i_name;
    QString i_contact_info;
    QString i_uri;
    QList<Companies> i_Sublabels;
    QList<QString> i_urls;
    QList<Images> i_Images;
    QString i_resourceUrl;
    QString i_data_quality;
    int i_id;

};

#endif // LABEL

