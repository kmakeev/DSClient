#include<header/search/videos.h>

Videos::Videos(const QString &description, const int &duration,const bool &embed, const QString &title, const QString &uri):
                i_description(description), i_duration(duration), i_embed(embed), i_title(title), i_uri(uri)

{

}
///******************************************************************************************************************
Videos::Videos()
{

}

///******************************************************************************************************************
Videos::~Videos()
{

}

///******************************************************************************************************************
QString Videos::description() const
{
    return i_description;
}


///******************************************************************************************************************
int Videos::duration() const
{
    return i_duration;

}


///******************************************************************************************************************
bool Videos::embed() const
{
    return i_embed;
}


///******************************************************************************************************************
QString Videos::title() const
{
    return i_title;
}


///******************************************************************************************************************
QString Videos::uri() const
{
    return i_uri;
}
