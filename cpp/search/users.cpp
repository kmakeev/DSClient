#include<header/search/users.h>

Users::Users(const QString &resourceUrl, const QString &username): i_resourceUrl(resourceUrl), i_username(username)
{
}

/// *************************************************************************
Users::~Users()
{

}

/// *************************************************************************
Users::Users()
{

}

/// *************************************************************************
QString Users::resourceUrl() const
{
    return i_resourceUrl;
}

/// *************************************************************************
QString Users::username() const
{
    return i_username;
}

/// *************************************************************************
///
