#ifndef MEMBERS
#define MEMBERS

#include <QVariant>


class Members            // класс для хранения информации об участниках
{
public:
    //Констуктор
    Members (const bool &active,
                       const int &id,
                       const QString &name,
                       const QString &resourceUrl);


    Members();
    ~Members();

    //Функции для получения данных класса

    bool active() const;
    int id() const;
    QString name() const;
    QString resourceUrl() const;



private:                    //Данные

    bool i_active;
    int i_id;
    QString i_name;
    QString i_resourceUrl;




};
#endif // MEMBERS

