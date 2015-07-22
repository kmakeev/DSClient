#ifndef O1REQUESTOR_H
#define O1REQUESTOR_H

#include <QObject>
#include <QNetworkRequest>
#include <QByteArray>

#include "o1.h"

class QNetworkAccessManager;
class QNetworkReply;
class O1;

/// Makes authenticated requests using OAuth 1.0.
class O1Requestor: public QObject {
    Q_OBJECT


public:
//    explicit O1Requestor(QNetworkAccessManager *manager, O1 *authenticator, QObject *parent = 0);
    explicit O1Requestor(QObject *parent);

    void link();
    void linkWitchUnlink();

    bool onlinked();
    void unlink();

    /// Make a GET request with wiat
   bool getWithWait(const QNetworkRequest &req, QString &strReply, const int timeOut);
//   bool getWithWait(const QNetworkRequest &req, QByteArray &strReply, const int timeOut);
   bool getWithWaiting(QNetworkRequest &req, QString &strReply, const int timeOut);
   bool getWithWaiting(QNetworkRequest &req, QByteArray &strReply, const int timeOut);

   bool deleteWithWait (const QNetworkRequest &req, const int timeOut);
   bool putWithWait(const QNetworkRequest &req, const QByteArray &data, const int timeOut);
   bool postWithWait(const QNetworkRequest &req, const QByteArray &data, QString &strReply, const int timeOut);

   bool readReplyData(QNetworkReply * reply, QString &strReply);
   bool readReplyData(QNetworkReply * reply, QByteArray &strReply);
   void wait(QNetworkReply* reply, int timeOut);
   bool loadImage(const QString & imageUrl, QImage & image);
   void setValue(const QString &key, const QString &value);
   QString value(const QString &key, const QString &defaultValue = QString());
   bool isLoggin();
   void setIsLoggin(const bool &a);

   bool isOffline();
   void setIsOffline(const bool &a);

   QByteArray createQueryParams(const QList<O1RequestParameter> &params);
//   QByteArray createJsonParams(const QList<O1RequestParameter> &params);




    static O1Requestor & instance()
    {
        static O1Requestor s(0);
        return s;
    }


signals:
      void onLoginSucceeded();
      void onLoginFailed();


public slots:


    /// Make a GET request.
    /// @param  req                 Network request.
    /// @param  signingParameters   Extra (non-OAuth) parameters participating in signing.
    /// @return Reply.
    QNetworkReply *get(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters);

    /// Make a POST request.
    /// @param  req                 Network request.
    /// @param  signingParameters   Extra (non-OAuth) parameters participating in signing.
    /// @param  data                Request payload.
    /// @return Reply.
    QNetworkReply *post(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters, const QByteArray &data);

    /// Make a POST request.
    /// @param  req                 Network request.
    /// @param  signingParameters   Extra (non-OAuth) parameters participating in signing.
    /// @param  multiPart           HTTPMultiPart.
    /// @return Reply.
    QNetworkReply *post(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters, QHttpMultiPart *multiPart);

    /// Make a PUT request.
    /// @param  req                 Network request.
    /// @param  signingParameters   Extra (non-OAuth) parameters participating in signing.
    /// @param  data                Request payload.
    /// @return Reply.
    QNetworkReply *put(const QNetworkRequest &req, const QList<O1RequestParameter> &signingParameters, const QByteArray &data);

    /// To link
    void onLinkedChanged();
    void onLinkingSucceeded();
    void onLinkingFailed();
    void onOpenBrowser(const QUrl &url);
    void onCloseBrowser();

protected:
    /// Return true if linked


    /// Return new request based on the original, with the "Authentication:" header added.
    QNetworkRequest setup(const QNetworkRequest &request, const QList<O1RequestParameter> &signingParameters, QNetworkAccessManager::Operation operation);

    QNetworkRequest setup(const QNetworkRequest &req, QNetworkAccessManager::Operation operation);


    /// Augment reply with a timer.
    QNetworkReply *addTimer(QNetworkReply *reply);

    QNetworkAccessManager *manager_;
    O1 *authenticator_;
    //Для кеша картинок

    QHash<QString, QByteArray> m_cacheImage;

    //Если есть линк и есть удачное чтение профиля
    bool isLoggin_;
    // Если есть линк, но нет чтения профиля по сети
    bool isOffline_;


};


#endif // O1REQUESTOR_H
