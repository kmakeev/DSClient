//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickView>
#include <QVariant>
#include <QQmlEngine>
#include <QSettings>
#include <QQmlEngine>
//#include "ProfileModel.h"
#include "header\system\secureimageprovider.h"
#include <header\search\searchmodel.h>
#include <header\collection\collectionmodel.h>
#include <header\collection\fieldsmodel.h>
#include <header\user\profileModel.h>
#include <header\wantlist\wantlistmodel.h>





// #include <QQuickImageProvider>
#include <QTextCodec>



Q_DECL_EXPORT int main(int argc, char *argv[])

{

//   O1Requestor::instance();
   QGuiApplication app(argc, argv);

   qmlRegisterType<ProfileUserModel>("ProfileUserModel",1,0,"ProfileUserModel");
   qmlRegisterType<CollectionModel>("CollectionModel",1,0,"CollectionModel");
//   qmlRegisterType<CollectionSortModel>("SortModel",1,0,"SortModel");
   qmlRegisterType<SearchModel>("SearchModel",1,0,"SearchModel");
   qmlRegisterType<WantlistModel>("WantlistModel",1,0,"WantlistModel");
   qmlRegisterType<FieldsModel>("FieldsModel",1,0,"FieldsModel");


   QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
   QCoreApplication::setOrganizationName("Discogs");
   QCoreApplication::setOrganizationDomain("discogs.com");
   QCoreApplication::setApplicationName("Discogs client");
   QQmlApplicationEngine engine;

   // set secureimageprovider for qml
   engine.addImageProvider(QString("MyImageProvider"), new SecureImageProvider());

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



   return app.exec();
}
