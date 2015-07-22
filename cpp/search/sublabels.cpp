#include<header/search/sublabels.h>

Sublabels::Sublabels (const QString &resourseUrl, const int &id, const QString &name): i_resourseUrl(resourseUrl), i_id(id), i_name(name).
{

}




int id() const;
QString name() const;
QString resourseUrl() const;
