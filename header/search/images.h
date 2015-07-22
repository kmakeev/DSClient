#ifndef IMAGES
#define IMAGES

#include <QVariantList>


class Images            // класс для хранения информации о картинках
{
public:
    //Констуктор
    Images (const int &height,
                       const int &width,
                       const QString &resourceUrl,   //подумать стоит ли хранить бинарную картинку в классе и устанавливать признак ее загрузки
                       const QString &uri,
                       const QString &uri150,
                       const QString &type);
    Images();

    ~Images();



    //Функции для получения данных класса

    int height() const;
    int width() const;
    QString resourceUrl() const;
    QString uri() const;
    QString uri150() const;
    QString type;



private:                    //Данные

    int i_height;
    int i_width;
    QString i_resourceUrl;
    QString i_uri;
//    QString i_urls;
    QString i_uri150;
    QString i_type;



};

#endif // IMAGES

