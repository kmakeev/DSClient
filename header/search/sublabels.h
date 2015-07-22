#ifndef SUBLABELS
#define SUBLABELS

#include <QVariant>


class Sublabels            // класс для хранения информации об участниках
{
public:
    //Констуктор
    Sublabels (const QString &resourseUrl,
                       const int &id,
                       const QString &name);

    //Функции для получения данных класса


    int id() const;
    QString name() const;
    QString resourseUrl() const;



private:                    //Данные


    int i_id;
    QString i_name;
    QString i_resourseUrl;


};

#endif // SUBLABELS

