#include<header/search/raiting.h>



Raiting::Raiting(const int &average, const int count):i_average(average), i_count(count)
{

}

/// *************************************************************************
Raiting::Raiting()
{

}

/// *************************************************************************
Raiting::~Raiting()
{

}

/// *************************************************************************
int Raiting::average() const
{
    return i_average;
}

/// *************************************************************************
int Raiting::count() const
{
    return i_count;
}



