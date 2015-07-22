#ifndef BASICINFO_H
#define BASICINFO_H
#include <QVariant>
#include<header/search/artists.h>
#include<header/search/formats.h>
#include<header/search/label.h>
#include<header/collection/notes.h>


class BasicInfo
{
public:
    BasicInfo(const int &id, const QString &title, const int &year, const QString &resourceURL, const QString &thumb,
              const Formats &formats, const QList<Companies> &labels, const Artists &artists, const QList<Notes> &notes);

    BasicInfo();
    ~BasicInfo();

    int id() const;
    QString title() const;
    int year() const;
    QString resourceURL() const;
    QString thumb() const;
    Formats formats() const;
    QList<Companies> labels() const;
    Artists artists() const;
    QList<Notes> notes() const;


private:

    int f_id;
    QString f_title;
    int f_year;
    QString f_resourceURL;
    QString f_thumb;
    Formats f_formats;
    QList<Companies> f_labels;
    Artists f_artists;
    QList<Notes> f_notes;



};

#endif // BASICINFO_H
