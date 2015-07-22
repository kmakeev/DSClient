#ifndef COMPANIES
#define COMPANIES

#include <QVariant>

class Companies
{
public:
    Companies(const QString &catno, const QString &entity_type, const QString &entity_type_name, const int &id, const QString &name, const QString &resourceUrl);

    Companies();
    ~Companies();

    QString catno() const;
    QString entity_type() const;
    QString entity_type_name() const;
    int id() const;
    QString name() const;
    QString resourceUrl() const;

private:

    QString i_catno;
    QString i_entity_type;
    QString i_entity_type_name;
    int i_id;
    QString i_name;
    QString i_resourceUrl;

};

#endif // COMPANIES

