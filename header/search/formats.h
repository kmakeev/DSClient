#ifndef FORMATS
#define FORMATS

#include <QVariant>

class Formats
{
public:

    Formats(const QList<QString> &description, const QString &name, const QString &qty); //Для want не хватает taxt, можно сделать перегружаемый конструктор с этим полем
    Formats();
    ~Formats();


    QList<QString> description() const;
    QString name() const;
    QString qty() const;

private:
    QList<QString> i_description;
    QString i_name;
    QString i_qty;


};

#endif // FORMATS

