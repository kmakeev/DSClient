#include "header\collection\basicinfo.h"

BasicInfo::BasicInfo(const int &id, const QString &title, const int &year, const QString &resourceURL, const QString &thumb,
                     const Formats &formats, const QList<Companies> &labels, const Artists &artists, const QList<Notes> &notes):
                     f_id(id), f_title(title), f_year(year), f_resourceURL(resourceURL), f_thumb(thumb),f_formats(formats), f_labels(labels), f_artists(artists),f_notes(notes)
{

}
///******************************************************************************************************************
///
BasicInfo::BasicInfo()
{

}

///******************************************************************************************************************

int BasicInfo::id() const
{
    return f_id;
}
///******************************************************************************************************************
QString BasicInfo::title() const
{
    return f_title;
}
///******************************************************************************************************************
int BasicInfo::year() const
{
    return f_year;
}
///******************************************************************************************************************
QString BasicInfo::resourceURL() const
{
    return f_resourceURL;
}
///******************************************************************************************************************
QString BasicInfo::thumb() const
{
    return f_thumb;
}
///******************************************************************************************************************
BasicInfo::~BasicInfo()
{

}
///******************************************************************************************************************
Formats BasicInfo::formats() const
{
    return f_formats;
}

QList<Companies> BasicInfo::labels() const
{
    return f_labels;
}
///******************************************************************************************************************
Artists BasicInfo::artists() const
{
    return f_artists;
}
///******************************************************************************************************************
QList<Notes> BasicInfo::notes() const
{
    return f_notes;
}
///******************************************************************************************************************
