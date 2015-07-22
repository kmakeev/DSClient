#ifndef PROFILEMODEL_H
#define PROFILEMODEL_H

#include <QObject>
#include <QStringList>
#include <QString>
#include <header/user/profileuser.h>



class ProfileUserModel : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString userName READ userName)
    Q_PROPERTY(QString email READ email)
    Q_PROPERTY(QString glocation READ glocation)
    Q_PROPERTY(QString profile READ profile NOTIFY profileChanged)
    Q_PROPERTY(QString homePage READ homePage NOTIFY homePageChanged)
    Q_PROPERTY(bool isLoggin READ isLoggin NOTIFY isLogginChanged)                          //Признак того, что пользователь залогинен, потом подумать и можно сделать по аналогии хранение в синглетоне
    Q_PROPERTY(bool isOffline READ isOffline NOTIFY isOfflineChanged)                          //Признак того, что пользователь залогинен
    Q_PROPERTY(QString avatarUrl READ avatarUrl)
    Q_PROPERTY(int numCollection READ numCollection)
    Q_PROPERTY(int numWantList READ numWantList)
    Q_PROPERTY(QString registered READ registered)


public:

    ProfileUserModel();
    ~ProfileUserModel();

    Q_INVOKABLE QString name();
//    Q_INVOKABLE void setName (QString &name);

    Q_INVOKABLE QString userName();

    Q_INVOKABLE QString email();

    Q_INVOKABLE QString profile();
 //   Q_INVOKABLE void setProfile (QString &profile);

    Q_INVOKABLE QString homePage();

    Q_INVOKABLE QString glocation();

    Q_INVOKABLE bool isLoggin();

    Q_INVOKABLE bool isOffline();

    Q_INVOKABLE void logout();

    Q_INVOKABLE void login();

    Q_INVOKABLE QString avatarUrl();

    Q_INVOKABLE int numCollection();

    Q_INVOKABLE int numWantList();

    Q_INVOKABLE QString registered();

    Q_INVOKABLE bool saveUserProfile(QString username, QString name, QString home_page, QString location_, QString profile);

    bool getInfoProfile(QString &u);

    void refreshInfoProfile(QJsonObject &jsonObj);

    void getProfileFromStore();

private slots:

    void onLoggin();
    void onLogginFailed();

signals:
    void nameChanged();
    void profileChanged();
    void homePageChanged();
    void isLogginChanged();
    void isOfflineChanged();



private:
    ProfileUser m_ProfileUser;
    bool m_isLoggin;
    int timeOut;



};

#endif // PROFILEMODEL_H
