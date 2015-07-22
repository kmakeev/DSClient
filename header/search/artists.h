#ifndef ARTISTS
#define ARTISTS

#include <QString>

class Artists
{
public:
    //Констуктор
    Artists (const QString &anv,
                       const int &id,
                       const QString &join,
                       const QString &name,
                       const QString &resourceUrl,
                       const QString &role,
                       const QString &tracks);


    Artists();
    ~Artists();

    //Функции для получения данных класса

    QString anv() const;
    int id() const;
    QString join() const;
    QString name() const;
    QString resourceUrl() const;
    QString role() const;
    QString tracks() const;




private:                    //Данные

    QString i_anv;
    int i_id;
    QString i_join;
    QString i_name;
    QString i_resourceUrl;
    QString i_role;
    QString i_tracks;


};



#endif // ARTISTS

