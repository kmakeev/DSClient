#ifndef FOLDERS_H
#define FOLDERS_H
#include <QVariant>


class Folders
{
public:
    Folders(const int &id, const int &count, const QString &name, const QString &resourceUrl);
    ~Folders();
    Folders();


    int id() const;
    int count() const;
    QString name() const;
    QString resourceUrl() const;

private:
    int f_id;
    int f_count;
    QString f_name;
    QString f_resourceUrl;

};

#endif // FOLDERS_H
