#ifndef IDENTIFIERS
#define IDENTIFIERS

#include <QString>

class Identifiers
{
public:
    Identifiers(const QString &type, const QString &value);

    Identifiers();
    ~Identifiers();

     QString type() const;
     QString value() const;

private:
     QString m_type;
     QString m_value;

};

#endif // IDENTIFIERS

