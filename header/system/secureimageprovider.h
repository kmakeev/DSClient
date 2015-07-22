//******************************************************************************
//******************************************************************************

#ifndef SECUREIMAGEPROVIDER_H
#define SECUREIMAGEPROVIDER_H

#include <QQuickImageProvider>
// #include <QQmlImageProviderBase>


//******************************************************************************

class SecureImageProvider : public QQuickImageProvider
{
protected:



public:
    SecureImageProvider();

    virtual QImage  requestImage (const QString & id, QSize * size, const QSize & requestedSize);
    virtual QPixmap requestPixmap(const QString & id, QSize * size, const QSize & requestedSize);

};


#endif // SECUREIMAGEPROVIDER_H
