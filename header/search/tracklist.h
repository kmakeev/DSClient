#ifndef TRACKLIST
#define TRACKLIST

#include <QVariant>
#include <header/search/artists.h>

class Tracklist
{
public:
    Tracklist(const QString &duration, const QList<Artists> &extraartists, const QString &position, const QString &title, const QString &type_);
    Tracklist();
    ~Tracklist();


    QString duration() const;
    QList<Artists> extaartists() const;
    QString position() const;
    QString title() const;
    QString type_() const;

private:
    QString i_duration;
    QList<Artists> i_extraartists;
    QString i_position;
    QString i_title;
    QString i_type_;

};

#endif // TRACKLIST

