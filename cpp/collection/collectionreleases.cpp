#include<header\collection\collectionreleases.h>


CollectionReleases::CollectionReleases(const int &id, const int &instance_id, const int &folder_id, const int &rating, const BasicInfo &basicInformation):
                                       f_id(id), f_instance(instance_id), f_folder_id(folder_id), f_rating(rating), f_basicInformation(basicInformation)


{

}

///******************************************************************************************************************
CollectionReleases::CollectionReleases()
{

}

///******************************************************************************************************************
int CollectionReleases::id() const
{
  return f_id;
}
///******************************************************************************************************************
int CollectionReleases::instance() const
{
    return f_instance;
}
///******************************************************************************************************************
int CollectionReleases::folder_id() const
{
    return f_folder_id;
}
///******************************************************************************************************************
int CollectionReleases::rating() const
{
    return f_rating;
}
///******************************************************************************************************************
BasicInfo CollectionReleases::basicInformation() const
{
    return f_basicInformation;
}
///******************************************************************************************************************
CollectionReleases::~CollectionReleases()
{

}

