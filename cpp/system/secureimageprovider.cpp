//******************************************************************************
//******************************************************************************

#include "header\system\secureimageprovider.h"
#include "header\system\o1requestor.h"

#include <QDebug>


//******************************************************************************
//******************************************************************************
SecureImageProvider::SecureImageProvider()
    : QQuickImageProvider (QQuickImageProvider::Image)
{
}

//******************************************************************************
//******************************************************************************
QImage SecureImageProvider::requestImage(const QString & id, QSize * size,
                                         const QSize & requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)

//    qDebug() << Q_FUNC_INFO << id;

    QImage resultImage;

    if (!id.isEmpty() && O1Requestor::instance().loadImage(id, resultImage))
    {
        return resultImage;

    }  else {
        qDebug() << Q_FUNC_INFO << id << " Ошибка загрузки картинки";

        resultImage.load(":/pics/default.png");
        return resultImage;
    }

}


//******************************************************************************
//******************************************************************************
QPixmap SecureImageProvider::requestPixmap(const QString & id, QSize * size,
                                           const QSize & requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)

 //   qDebug() << Q_FUNC_INFO << id;
    return QPixmap();
}

