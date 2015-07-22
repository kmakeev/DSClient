#include<header/search/tracklist.h>

Tracklist::Tracklist(const QString &duration, const QList<Artists> &extraartists, const QString &position, const QString &title, const QString &type_): i_duration(duration), i_extraartists(extraartists), i_position(position),i_title(title), i_type_(type_)
{

}
///******************************************************************************************************************
Tracklist::Tracklist()
{

}
///******************************************************************************************************************
Tracklist::~Tracklist()
{

}

///******************************************************************************************************************
QString Tracklist::duration() const
{
    return i_duration;

}

///******************************************************************************************************************
QList<Artists> Tracklist::extaartists() const
 {
     return i_extraartists;
 }

///******************************************************************************************************************
QString Tracklist::position() const
{
    return i_position;
}

///******************************************************************************************************************
QString Tracklist::title() const
{
    return i_title;
}

///******************************************************************************************************************
QString Tracklist::type_() const
{
    return i_type_;
}
