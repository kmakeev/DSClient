#ifndef NOTES_H
#define NOTES_H
#include <QVariant>


class Notes
{
public:
    Notes(const int &field_id, const QString &value);
    Notes();
    ~Notes();


    int field_id() const;
    QString value() const;

private:
    int i_field_id;
    QString i_value;
};

#endif // NOTES_H
