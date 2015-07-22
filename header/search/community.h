#ifndef COMMUNITY
#define COMMUNITY

#include<header/search/users.h>
#include<header/search/raiting.h>
#include <QString>




class Community
{
public:
    //Констуктор
    Community (const QList<Users> &contributors,
                       const QString &data_quality,
                       const int &have,
                       const Raiting &raiting,
                       const QString &status,
                       const Users &submitter,
                       const int &want);


    Community();
    ~Community();


    //Функции для получения данных класса

    QList<Users> contributors() const;
    QString data_quality() const;
    int have() const;
    Raiting raiting() const;
    QString status() const;
    Users submitter() const;
    int want() const;





private:                    //Данные

    QList<Users> i_contributors;
    QString i_data_quality;
    int i_have;
    Raiting i_raiting;
    QString i_status;
    Users i_submitter;
    int i_want;

};


#endif // COMMUNITY

