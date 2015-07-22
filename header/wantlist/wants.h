#ifndef WANTS_H
#define WANTS_H
#include <header/collection/basicinfo.h>



class Wants
{

public:
    Wants(const int &rating, const BasicInfo &basicInformation, const QString &resourceUrl, const int &id);
    Wants();
    ~Wants();

     int rating() const;
     BasicInfo basicInformation() const;
     QString resourceUrl() const;
     int id() const;

private:
     int w_rating;
     BasicInfo w_basicInformation;
     QString w_resourceUrl;
     int w_id;

};

#endif // WANTS_H
