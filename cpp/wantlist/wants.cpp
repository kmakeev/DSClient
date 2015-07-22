#include "header/wantlist/wants.h"


Wants::Wants(const int &rating, const BasicInfo &basicInformation, const QString &resourceUrl, const int &id):w_rating(rating), w_basicInformation(basicInformation), w_resourceUrl(resourceUrl), w_id(id)
{


}

///******************************************************************************************************************
Wants::Wants()
{


}

///******************************************************************************************************************


Wants::~Wants()
{

}

///******************************************************************************************************************
int Wants::rating() const
{
    return w_rating;
}

///******************************************************************************************************************
BasicInfo Wants::basicInformation() const
{
    return w_basicInformation;
}

///******************************************************************************************************************
QString Wants::resourceUrl() const
{
    return w_resourceUrl;
}

///******************************************************************************************************************
int Wants::id() const
{
    return w_id;
}
