#ifndef FIELDS_H
#define FIELDS_H
#include<QVariant>
#include <header\collection\mainlistmodel.h>



class Fields
{
//    Q_OBJECT

public:

    Fields(const QString &name, const QStringList &options, const int &id, const int &position, const QString &type, const bool &public_, const int &lines, const bool &isDropdown);

    Fields();

    ~Fields();

    QString name() const;
    QStringList options() const;
    int id() const;
    int position() const;
    QString type() const;
    bool public_() const;
    int lines() const;
    bool isDropdown() const;
    QStringListModel * model_() const;


private:
    QString f_name;
    QStringList f_options;
    int f_id;
    int f_position;
    QString f_type;
    bool f_public_;
    int f_lines;
    bool f_isDropdown;

    QStringListModel *f_model;


public:


};

#endif // FIELDS_H
