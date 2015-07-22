#include "header/user/profileModel.h"
#include "header/system/o1requestor.h"
#include <header/system/qmltyperegistrator.h>
#include <header/system/o2globals.h>

namespace {
QmlTypeRegistrator registrator(qmlRegisterType<ProfileUserModel>("ProfileUserModel",1,0,"ProfileUserModel"));
}

///******************************************************************************************************************

ProfileUserModel::ProfileUserModel()
{

    bool error = false;

    qDebug() << "ProfileModel constructor ";
    timeOut = 10000;       //определяем таймаут для работы с сетью. нужно сделать записимость от скорости ответа на запрос
    //  if (!O1Requestor::instance().onlinked())
    //   {
    O1Requestor::instance().link();
    if (!O1Requestor::instance().value("username").isEmpty())
    {
        O1Requestor::instance().setIsLoggin(true);             //Если в сторе есть имя пользователя, значит он был залогинен
        emit isLogginChanged();
    }
    QUrl url = QUrl(IDENTITY_STRING);    //Считаваем строку идентификации пользователя
    QNetworkRequest request(url);
    QString strReply;
    if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
    {
        qDebug() << "ERROR get identity";
        error = true;
    } else
    {

        qDebug() << "Identity read OK";
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        QString resourceUrl = jsonObj["resource_url"].toString();
        if (!resourceUrl.isEmpty())
            if(!getInfoProfile(resourceUrl))                                 //Если не считали по сети
                error= true;

    }

    if (error&&!O1Requestor::instance().value("username").isEmpty())
    {
        getProfileFromStore();
        O1Requestor::instance().setIsOffline(false);
        emit isOfflineChanged();
    }

}

///******************************************************************************************************************
void ProfileUserModel::logout()
{
    //    m_isLoggin = false;
    O1Requestor::instance().unlink();
    emit isLogginChanged();
    O1Requestor::instance().setIsOffline(false);
    emit isOfflineChanged();
    QFile wntlist(WANTLIST_FILENAME);
    if (wntlist.remove()) {qDebug() << "WANTLIST_FILENAME removed"; };
    QFile collection(COLLECTION_FILENAME);
    if (collection.remove()) {qDebug() << "COLLECTION_FILENAME removed"; };
    QFile folder(FOLDER_FILENAME);
    if (folder.remove()) {qDebug() << "FOLDER_FILENAME removed"; };
    QFile fields(FIELDS_FILENAME);
    if (fields.remove()) {qDebug() << "FOLDER_FILENAME removed"; };
    //Еще нужно очистить все модели в памяти, бодем делать из вью перед вызовом


}

///******************************************************************************************************************
void ProfileUserModel::login()
{
    //   m_isLoggin = false;
    //   O1Requestor::instance().setIsLoggin(false);
    //   emit isLogginChanged();
    connect(&O1Requestor::instance(), SIGNAL(onLoginSucceeded()), this, SLOT(onLoggin()));
    connect(&O1Requestor::instance(), SIGNAL(onLoginFailed()), this, SLOT(onLogginFailed()));

    O1Requestor::instance().linkWitchUnlink();
}
///******************************************************************************************************************
void ProfileUserModel::onLoggin()
{
    //Теперь это только при нажатии логин из вью
    disconnect(this,0,0,0);                   //отключаем все сигналы от синглтона
    QUrl url = QUrl(IDENTITY_STRING);
    QNetworkRequest request(url);
    QString strReply;
    if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
    {
        qDebug() << "ERROR get identity";
    } else
    {

        qDebug() << "Identity read OK";
        //    qDebug() << strReply.toLatin1();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        //    qDebug() << "JSONOBJ" << jsonObj;
        QString resourceUrl = jsonObj["resource_url"].toString();
        if (!resourceUrl.isEmpty())
            if(getInfoProfile(resourceUrl)) {
                O1Requestor::instance().setIsLoggin(true);
               emit isLogginChanged();
            }

    }

}

///******************************************************************************************************************
void ProfileUserModel::onLogginFailed()
{
    disconnect(this,0,0,0);
    qDebug() << "Loggin failed";
}

///******************************************************************************************************************
ProfileUserModel::~ProfileUserModel()
{

}
///******************************************************************************************************************
bool ProfileUserModel::getInfoProfile(QString &u)
{
    QUrl url = QUrl(u);
    QNetworkRequest request(url);
    QString strReply;


    if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
    {
        qDebug() << "ERROR get profile";
        return false;
    } else
    {
        qDebug() << "Profile read OK";

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
   //     qDebug() << "JSONOBJ" << jsonObj;
        refreshInfoProfile(jsonObj);

        // Записываем основные параметры в store
        O1Requestor::instance().setValue("profile",m_ProfileUser.profile());
        O1Requestor::instance().setValue("wantlist_url",m_ProfileUser.wantlistUrl());
        O1Requestor::instance().setValue("rank",QString::number(m_ProfileUser.rank()));
        O1Requestor::instance().setValue("num_pending",QString::number(m_ProfileUser.numPending()));
        O1Requestor::instance().setValue("id",QString::number(m_ProfileUser.id()));
        O1Requestor::instance().setValue("num_for_sale",QString::number(m_ProfileUser.numForSale()));
        O1Requestor::instance().setValue("home_page",m_ProfileUser.homePage());
        O1Requestor::instance().setValue("collection_folders_url",m_ProfileUser.collectionFoldersUrl());
        O1Requestor::instance().setValue("username",m_ProfileUser.username());
        O1Requestor::instance().setValue("collection_fields_url",m_ProfileUser.collectionFieldsUrl());
        O1Requestor::instance().setValue("releases_contributes",QString::number(m_ProfileUser.releasesContributed()));
        O1Requestor::instance().setValue("registered",m_ProfileUser.redistred().toString("dd.MM.yyyy"));
        O1Requestor::instance().setValue("rating_avg",QString::number(m_ProfileUser.raitingAvg()));
        O1Requestor::instance().setValue("num_collection",QString::number(m_ProfileUser.numCollection()));
        O1Requestor::instance().setValue("releases_raited",QString::number(m_ProfileUser.ReleasesRaited()));
        O1Requestor::instance().setValue("num_lists",QString::number(m_ProfileUser.numLists()));
        O1Requestor::instance().setValue("name",m_ProfileUser.name());
        O1Requestor::instance().setValue("num_wantlist",QString::number(m_ProfileUser.numWantlist()));
        O1Requestor::instance().setValue("iventory_url",m_ProfileUser.inventoryUrl());
        O1Requestor::instance().setValue("avatar_url",m_ProfileUser.avatarUrl());
        O1Requestor::instance().setValue("uri",m_ProfileUser.uri());
        O1Requestor::instance().setValue("resource_url",m_ProfileUser.resourceUrl());
        O1Requestor::instance().setValue("email",m_ProfileUser.email());
        O1Requestor::instance().setValue("location",m_ProfileUser.location());


        return true;
    }
}


void ProfileUserModel::getProfileFromStore()
{

    m_ProfileUser = ProfileUser(O1Requestor::instance().value("profile"),
                O1Requestor::instance().value("wantlist_url"),
                O1Requestor::instance().value("rank").toInt(),
                O1Requestor::instance().value("num_pending").toInt(),
                O1Requestor::instance().value("id").toInt(),
                O1Requestor::instance().value("num_for_sale").toInt(),
                O1Requestor::instance().value("home_page"),
                O1Requestor::instance().value("collection_folders_url"),
                O1Requestor::instance().value("username"),
                O1Requestor::instance().value("collection_fields_url"),
                O1Requestor::instance().value("releases_contributes").toInt(),
                QDateTime::fromString(O1Requestor::instance().value("registered"),"yyyy-MM-ddThh:mm:ss"),
                O1Requestor::instance().value("rating_avg").toInt(),
                O1Requestor::instance().value("num_collection").toInt(),
                O1Requestor::instance().value("releases_raited").toInt(),
                O1Requestor::instance().value("num_lists").toInt(),
                O1Requestor::instance().value("name"),
                O1Requestor::instance().value("num_wantlist").toInt(),
                O1Requestor::instance().value("iventory_url"),
                O1Requestor::instance().value("avatar_url"),
                O1Requestor::instance().value("uri"),
                O1Requestor::instance().value("resource_url"),
                O1Requestor::instance().value("email"),
                O1Requestor::instance().value("location"));

}



void ProfileUserModel::refreshInfoProfile(QJsonObject &jsonObj)
{
    m_ProfileUser = ProfileUser(jsonObj["profile"].toString(),
    jsonObj["wantlist_url"].toString(),
    jsonObj["rank"].toInt(),
    jsonObj["num_pending"].toInt(),
    jsonObj["id"].toInt(),
    jsonObj["num_for_sale"].toInt(),
    jsonObj["home_page"].toString(),
    jsonObj["collection_folders_url"].toString(),
    jsonObj["username"].toString(),
    jsonObj["collection_fields_url"].toString(),
    jsonObj["releases_contributed"].toInt(),
    QDateTime::fromString(jsonObj["registered"].toString(),"yyyy-MM-ddThh:mm:ss"),
    jsonObj["rating_avg"].toInt(),
    jsonObj["num_collection"].toInt(),
    jsonObj["releases_raited"].toInt(),
    jsonObj["num_lists"].toInt(),
    jsonObj["name"].toString(),
    jsonObj["num_wantlist"].toInt(),
    jsonObj["inventory_url"].toString(),
    jsonObj["avatar_url"].toString(),
    jsonObj["uri"].toString(),
    jsonObj["resource_url"].toString(),
    jsonObj["email"].toString(),
    jsonObj["location"].toString());


}

///******************************************************************************************************************
/// Сохранение профила пользователя через API
bool ProfileUserModel::saveUserProfile(QString username, QString name, QString home_page, QString location_, QString profile)
{

    //Отредактировать профиль через API
    QString strReply;   //Для получения считанного после сохранения профиля
    QJsonObject array;
    array.insert(QString("username"),QJsonValue(username));
    array.insert(QString("name"),QJsonValue(name));
    array.insert(QString("home_page"),QJsonValue(home_page));
    array.insert(QString("location"),QJsonValue(location_));
    array.insert(QString("profile"),QJsonValue(profile));
    QJsonDocument param = QJsonDocument(array);
    QNetworkRequest request(QUrl(m_ProfileUser.resourceUrl()));

    if (!O1Requestor::instance().postWithWait(request, param.toJson(),strReply, timeOut))
    {

        qDebug() << "ERROR Edit Profile: ";
        return false;

    } else {
        qDebug() << "Profile saved ";    //Нам возврашается тоже что и при чтении профиля
        qDebug() << "Ответ" << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        refreshInfoProfile(jsonObj);
        return true;
    }

}

///
QString ProfileUserModel::name()
{
    return m_ProfileUser.name();
}

///******************************************************************************************************************
QString ProfileUserModel::userName()
{
    return m_ProfileUser.username();
}


///******************************************************************************************************************
QString ProfileUserModel::email()
{
 return m_ProfileUser.email();
}

///******************************************************************************************************************
QString ProfileUserModel::profile()
{
    return m_ProfileUser.profile();
}

///******************************************************************************************************************
QString ProfileUserModel::homePage()
{
    return m_ProfileUser.homePage();
}

///******************************************************************************************************************
QString ProfileUserModel::glocation()
{
    return m_ProfileUser.location();
}

///******************************************************************************************************************
bool ProfileUserModel::isLoggin()
{
    return O1Requestor::instance().isLoggin();
}

///******************************************************************************************************************
bool ProfileUserModel::isOffline()
{
    return O1Requestor::instance().isOffline();
}

///******************************************************************************************************************
QString ProfileUserModel::avatarUrl()
{
    return m_ProfileUser.avatarUrl();
}
///******************************************************************************************************************
int ProfileUserModel::numCollection()
{
     return m_ProfileUser.numCollection();
}
///******************************************************************************************************************
int ProfileUserModel::numWantList()
{
    return m_ProfileUser.numWantlist();
}

///******************************************************************************************************************
QString ProfileUserModel::registered()
{
    return m_ProfileUser.redistred().toString("dd.MM.yyyy");
}






