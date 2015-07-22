#ifndef COLLECTIONRELEASES_H
#define COLLECTIONRELEASES_H
#include <QVariant>
#include<header/search/artists.h>
#include<header/search/formats.h>
#include<header/search/label.h>
#include<header/collection/basicinfo.h>

class CollectionReleases
{
public:
    CollectionReleases(const int &id, const int &instance_id, const int &folder_id, const int &rating, const BasicInfo &basic_information);
    CollectionReleases();
    ~CollectionReleases();

    int id() const;
    int instance() const;
    int folder_id() const;
    int rating() const;
    BasicInfo basicInformation() const;



private:
    int f_id;
    int f_instance;
    int f_folder_id;
    int f_rating;
    BasicInfo f_basicInformation;







};

#endif // COLLECTIONRELEASES_H
