#include <header/search/community.h>


Community::Community (const QList<Users> &contributors,
                      const QString &data_quality,
                      const int &have,
                      const Raiting &raiting,
                      const QString &status,
                      const Users &submitter,
                      const int &want): i_contributors(contributors), i_data_quality(data_quality), i_have(have), i_raiting(raiting),
    i_status(status), i_submitter(submitter), i_want(want)
{

}

/// *************************************************************************
Community::Community()
{

}

/// *************************************************************************
Community::~Community()
{

}
//Функции для получения данных класса

/// *************************************************************************
QList<Users> Community::contributors() const
{
    return i_contributors;
}

/// *************************************************************************
QString Community::data_quality() const
{
    return i_data_quality;
}

/// *************************************************************************
int Community::have() const
{
    return i_have;
}

/// *************************************************************************
Raiting Community::raiting() const
{
    return i_raiting;
}

/// *************************************************************************
QString Community::status() const
{
    return i_status;
}

/// *************************************************************************
Users Community::submitter() const
{
    return i_submitter;
}

/// *************************************************************************
int Community::want() const
{
    return i_want;
}


