#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QDesktopServices>

#include "header\system\o1requestor.h"
#include "header\system\o2globals.h"
#include "header\system\verify.h"

#include <QEventLoop>

#include <QImage>


/// A timer connected to a network reply.
///
class TimedReply: public QTimer {
    Q_OBJECT

public:
    explicit TimedReply(QNetworkReply *parent): QTimer(parent) {
        setSingleShot(true);
        setInterval(600 * 1000); // FIXME: Expose me
        connect(this, SIGNAL(error(QNetworkReply::NetworkError)), parent, SIGNAL(error(QNetworkReply::NetworkError)));
        connect(this, SIGNAL(timeout()), this, SLOT(onTimeout()));
    }
///*****************************************************************************************

signals:
    void error(QNetworkReply::NetworkError);

public slots:
    void onTimeout() {emit error(QNetworkReply::TimeoutError);}
};
///*****************************************************************************************

O1Requestor::O1Requestor(QObject *parent): QObject(parent) {
    manager_ = new QNetworkAccessManager(this);
    authenticator_ = new O1(manager_,this);
    isLoggin_ = false;
    isOffline_ = false;



}
///*****************************************************************************************
bool O1Requestor::onlinked(){

    return  authenticator_->linked();
//    return linked;

}
///*****************************************************************************************
void O1Requestor::wait(QNetworkReply* reply, int timeOut)
{
    QEventLoop loop;

    VERIFY(connect(reply, SIGNAL(finished()), &loop, SLOT(quit())));
    if (timeOut > 0)
    {
        QTimer::singleShot(timeOut, &loop, SLOT(quit()));
    }

    loop.exec(QEventLoop::ExcludeUserInputEvents);
    VERIFY(disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit())));

}
///*****************************************************************************************
void O1Requestor::setValue(const QString &key, const QString &value)
{
   authenticator_->store_->setValue(key,value);
}

///*****************************************************************************************
QString O1Requestor::value(const QString &key, const QString &defaultValue)
{
    return authenticator_->store_->value(key,defaultValue);
}


///*****************************************************************************************

bool O1Requestor::isLoggin()
{
    return isLoggin_;
}
///*****************************************************************************************
void O1Requestor::setIsLoggin(const bool &a)
{
   isLoggin_=a;
}

///*****************************************************************************************

bool O1Requestor::isOffline()
{
    return isOffline_;
}
///*****************************************************************************************
void O1Requestor::setIsOffline(const bool &a)
{
   isOffline_=a;
}


///*****************************************************************************************

///*****************************************************************************************
bool O1Requestor::loadImage(const QString & imageUrl, QImage & image)
{

    QByteArray answer;
    if (m_cacheImage.contains(imageUrl))
    {
        answer = m_cacheImage[imageUrl];
    } else {
        QUrl url = QUrl(imageUrl);
        QNetworkRequest request(url);

        if (!getWithWaiting(request, answer,10000) || answer.isEmpty())
        {
            qDebug() << Q_FUNC_INFO << "Ошибка получения картинки";
            return false;
        }
            m_cacheImage.insert(imageUrl,answer);
        }
        image = QImage::fromData(answer);
        return true;

    }


bool O1Requestor::getWithWaiting (QNetworkRequest &req, QString &strReply, const int timeOut)
{


    QNetworkRequest request =req;
    request.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);
    request.setRawHeader("User-Agent", O2_CLIENT_NAME); //Добавлено для API Discogs


    QNetworkReply * reply = manager_->get(request);

            wait(reply, timeOut);
        return readReplyData(reply, strReply);

}





bool O1Requestor::getWithWait (const QNetworkRequest &req, QString &strReply, const int timeOut)
{

      QNetworkRequest request = setup(req, QNetworkAccessManager::GetOperation);
      QNetworkReply * reply = manager_->get(request);

            wait(reply, timeOut);
 //           qDebug() << Q_FUNC_INFO << "Exit Get withwait";
        return readReplyData(reply, strReply);

}


bool O1Requestor::getWithWaiting (QNetworkRequest &req, QByteArray &strReply, const int timeOut)
{


    req.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);
    req.setRawHeader("User-Agent", O2_CLIENT_NAME); //Добавлено для API Discogs
    QNetworkReply * reply = manager_->get(req);
            wait(reply, timeOut);
        return readReplyData(reply, strReply);

}


bool O1Requestor::deleteWithWait (const QNetworkRequest &req, const int timeOut)
{

    QNetworkRequest request = setup(req, QNetworkAccessManager::GetOperation);
    QNetworkReply * reply = manager_->deleteResource(request);

    wait(reply, timeOut);
    if (reply->error() == QNetworkReply::NoError)
    {
        reply->deleteLater();
        return true;
    }
    else {
        qDebug() << reply->error();
        return false;
    }
}


bool O1Requestor::putWithWait(const QNetworkRequest &req, const QByteArray &data,const int timeOut)
{
    QString strReply;
    QNetworkRequest request = setup(req, QNetworkAccessManager::PutOperation);
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QNetworkReply * reply = manager_->put(request,data);

    wait(reply, timeOut);
    if (reply->error() == QNetworkReply::NoError)
    {
        reply->deleteLater();
        strReply = reply->readAll();
        return true;
    }
    else {
       strReply = reply->readAll();

        return false;
    }
}

bool O1Requestor::postWithWait(const QNetworkRequest &req, const QByteArray &data, QString &strReply, const int timeOut)
{


    QNetworkRequest request = setup(req, QNetworkAccessManager::PostOperation);
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");                      //Определяем формат передаваемых параметров

    QNetworkReply * reply = manager_->post(request,data);

    wait(reply, timeOut);
    qDebug() << reply->error();
    if (reply->error() == QNetworkReply::NoError)
    {

        reply->deleteLater();
        strReply = reply->readAll();
        return true;
    }
    else {
        qDebug() << reply->error();
        strReply = reply->readAll();
        return false;
    }
}

/*
bool O1Requestor::getWithWait(const QNetworkRequest &req, QByteArray &strReply, const int timeOut)
{

    QNetworkRequest request = setupWithoutSign(req, QNetworkAccessManager::GetOperation);
    QNetworkReply * reply = manager_->get(request);
//    qDebug() << Q_FUNC_INFO << "Get withwait";

          wait(reply, timeOut);

//     qDebug() << Q_FUNC_INFO << "Exit Get withwait";
     return readReplyData(reply, strReply);





}

*/
bool O1Requestor::readReplyData(QNetworkReply * reply, QString &strReply)

{

    if (reply->error() == QNetworkReply::NoError)
    {
      reply->deleteLater();
      strReply = reply->readAll();
//      qDebug() << strReply;
      return true;
    }
    else {
        qDebug() << reply->error();
        reply->deleteLater();
        return false;
         }
  }

bool O1Requestor::readReplyData(QNetworkReply * reply, QByteArray &strReply)

{
  if (reply->error() == QNetworkReply::NoError)
  {
    reply->deleteLater();
    strReply = reply->readAll();
    return true;
  }
  else {
      qDebug() << reply->error();
      return false;
       }
}


QNetworkReply *O1Requestor::get(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters) {

    QNetworkRequest request = setup(req, signingParameters, QNetworkAccessManager::GetOperation);
    return addTimer(manager_->get(request));
}

QNetworkReply *O1Requestor::post(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters, const QByteArray &data) {
    QNetworkRequest request = setup(req, signingParameters, QNetworkAccessManager::PostOperation);
    return addTimer(manager_->post(request, data));
}

QNetworkReply *O1Requestor::post(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters, QHttpMultiPart * multiPart) {
    QNetworkRequest request = setup(req, signingParameters, QNetworkAccessManager::PostOperation);
    return addTimer(manager_->post(request, multiPart));
}

QNetworkReply *O1Requestor::put(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters, const QByteArray &data) {
    QNetworkRequest request = setup(req, signingParameters, QNetworkAccessManager::PutOperation);
    return addTimer(manager_->put(request, data));
}

QNetworkReply *O1Requestor::addTimer(QNetworkReply *reply) {
    (void)new TimedReply(reply);
    return reply;
}



QNetworkRequest O1Requestor::setup(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters, QNetworkAccessManager::Operation operation) {
    // Collect OAuth parameters
 //   qDebug() << Q_FUNC_INFO << "Get setup";
    QList<O1RequestParameter> oauthParams;
    oauthParams.append(O1RequestParameter(O2_OAUTH_CONSUMER_KEY, authenticator_->clientId().toLatin1()));
    oauthParams.append(O1RequestParameter(O2_OAUTH_VERSION, "1.0"));
    oauthParams.append(O1RequestParameter(O2_OAUTH_TOKEN, authenticator_->token().toLatin1()));
    oauthParams.append(O1RequestParameter(O2_OAUTH_SIGNATURE_METHOD, authenticator_->signatureMethod().toLatin1()));
    oauthParams.append(O1RequestParameter(O2_OAUTH_NONCE, O1::nonce()));
    oauthParams.append(O1RequestParameter(O2_OAUTH_TIMESTAMP, QString::number(QDateTime::currentDateTimeUtc().toTime_t()).toLatin1()));

    // Add signature parameter
    oauthParams.append(O1RequestParameter(O2_OAUTH_SIGNATURE, authenticator_->generateSignature(oauthParams, req, signingParameters, operation)));

    // Return a copy of the original request with authorization header set
    QNetworkRequest request(req);
    request.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);
    request.setRawHeader("User-Agent", O2_CLIENT_NAME); //Добавлено для API Discogs
    request.setRawHeader(O2_HTTP_AUTHORIZATION_HEADER, O1::buildAuthorizationHeader(oauthParams));

//    qDebug() << Q_FUNC_INFO << "Exit setup";
    return request;
}

// Думаю стоит переделать
QNetworkRequest O1Requestor::setup(const QNetworkRequest &req, QNetworkAccessManager::Operation operation) {
    // Collect OAuth parameters
    QList<O1RequestParameter> oauthParams;
//    qDebug() << Q_FUNC_INFO << "Get setupWithoutSign";
    oauthParams.append(O1RequestParameter(O2_OAUTH_CONSUMER_KEY, authenticator_->clientId().toLatin1()));
    oauthParams.append(O1RequestParameter(O2_OAUTH_VERSION, "1.0"));
    oauthParams.append(O1RequestParameter(O2_OAUTH_TOKEN, authenticator_->token().toLatin1()));
    oauthParams.append(O1RequestParameter(O2_OAUTH_SIGNATURE_METHOD, authenticator_->signatureMethod().toLatin1()));
    oauthParams.append(O1RequestParameter(O2_OAUTH_NONCE, O1::nonce()));
    oauthParams.append(O1RequestParameter(O2_OAUTH_TIMESTAMP, QString::number(QDateTime::currentDateTimeUtc().toTime_t()).toLatin1()));
    //Всталено для совместимости
    QList<O1RequestParameter> signingParameters;
    //= QList<O1RequestParameter>();
    // Add signature parameter
    oauthParams.append(O1RequestParameter(O2_OAUTH_SIGNATURE, authenticator_->generateSignature(oauthParams, req, signingParameters, operation)));

    // Return a copy of the original request with authorization header set
    QNetworkRequest request(req);
    request.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);
    request.setRawHeader("User-Agent", O2_CLIENT_NAME); //Добавлено для API Discogs
    request.setRawHeader(O2_HTTP_AUTHORIZATION_HEADER, O1::buildAuthorizationHeader(oauthParams));
//    qDebug() << Q_FUNC_INFO << "Exit Get setupWithoutSign";
    return request;
}



QByteArray O1Requestor::createQueryParams(const QList<O1RequestParameter> &params) {
    QByteArray ret;
    bool first = true;
    foreach (O1RequestParameter h, params) {
        if (first) {
            first = false;
        } else {
            ret.append("&");
        }
        ret.append(QUrl::toPercentEncoding(h.name) + "=" + QUrl::toPercentEncoding(h.value));
    }
    return ret;
}
/*
QByteArray O1Requestor::createJsonParams(const QList<O1RequestParameter> &params) {
    QByteArray ret = "{";
    bool first = true;
    foreach (O1RequestParameter h, params) {
        if (first) {
            first = false;
        } else {
            ret.append(",");
        }
        ret.append("\""+h.name + "\""+": " + "\""+ h.value+"\"");
    }
    ret.append("}");
    return ret;
}
*/
void O1Requestor::  link()
{


    authenticator_->setClientId(O2_OAUTH2_CLIENT_ID);
    authenticator_->setClientSecret(O2_OAUTH2_CLIENT_SECRET);
    authenticator_->setRequestTokenUrl(QUrl(O2_REQUEST_TOKEN_URL));
    authenticator_->setAuthorizeUrl(QUrl(O2_AUTHORIZE_URL));
    authenticator_->setAccessTokenUrl(QUrl(O2_ACCESS_TOKEN_URL));
    authenticator_->setLocalPort(O2_LOCAL_PORT);

//    authenticator_->unlink();
/*
    connect(authenticator_, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(authenticator_, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(authenticator_, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    connect(authenticator_, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    connect(authenticator_, SIGNAL(closeBrowser()), this, SLOT(onCloseBrowser()));
    authenticator_->link();
*/
}

void O1Requestor::linkWitchUnlink()
{


    authenticator_->setClientId(O2_OAUTH2_CLIENT_ID);
    authenticator_->setClientSecret(O2_OAUTH2_CLIENT_SECRET);
    authenticator_->setRequestTokenUrl(QUrl(O2_REQUEST_TOKEN_URL));
    authenticator_->setAuthorizeUrl(QUrl(O2_AUTHORIZE_URL));
    authenticator_->setAccessTokenUrl(QUrl(O2_ACCESS_TOKEN_URL));
    authenticator_->setLocalPort(O2_LOCAL_PORT);
    authenticator_->unlink();

    connect(authenticator_, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(authenticator_, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(authenticator_, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    connect(authenticator_, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    connect(authenticator_, SIGNAL(closeBrowser()), this, SLOT(onCloseBrowser()));
    authenticator_->link();
}

void O1Requestor::unlink()
{
    authenticator_->unlink();
    isLoggin_=false;
    authenticator_->store_->clearSettings();

}


void O1Requestor::onOpenBrowser(const QUrl &url) {
    qDebug() << "Opening browser with url" << url.toString();
    QDesktopServices::openUrl(url);
}

void O1Requestor::onCloseBrowser() {
    //Вставить сюда код закрытия браузера
}

void O1Requestor::onLinkedChanged() {
    qDebug() << "Link changed!";
}

void O1Requestor::onLinkingSucceeded() {
    qDebug() << "LinkingSucceeded";
    disconnect(authenticator_,0,0,0);
    emit onLoginSucceeded();

    //    readIdentity();
}

void O1Requestor::onLinkingFailed() {
    qDebug() << "Linking Fail!";
    disconnect(authenticator_,0,0,0);
    emit onLoginFailed();
}




#include "o1requestor.moc"
