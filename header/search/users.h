#ifndef USERS
#define USERS
#include <QVariant>

class Users
{

public:
    Users(const QString &resourceUrl, const QString &username);
    Users();
    ~Users();


    QString resourceUrl() const;
    QString username() const;

private:
    QString i_resourceUrl;
    QString i_username;

};
#endif // USERS

