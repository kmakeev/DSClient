TEMPLATE = app

QT += declarative qml quick network

SOURCES += main.cpp \
    cpp/search/members.cpp \
    cpp/search/images.cpp \
    cpp/search/artist.cpp \
    cpp/search/label.cpp \
    cpp/search/artists.cpp \
    cpp/search/community.cpp \
    cpp/search/companies.cpp \
    cpp/search/formats.cpp \
    cpp/search/identifiers.cpp \
    cpp/search/master.cpp \
    cpp/search/tracklist.cpp \
    cpp/search/videos.cpp \
    cpp/search/release.cpp \
    cpp/search/raiting.cpp \
    cpp/search/users.cpp \
    cpp/system/o1.cpp \
    cpp/system/o1requestor.cpp \
    cpp/system/o2replyserver.cpp \
    cpp/system/o2settingsstore.cpp \
    cpp/system/simplecrypt.cpp \
    cpp/system/secureimageprovider.cpp \
    cpp/search/searchresult.cpp \
    cpp/search/searchmodel.cpp \
    cpp/collection/folders.cpp \
    cpp/collection/collectionreleases.cpp \
    cpp/collection/basicinfo.cpp \
    cpp/collection/fields.cpp \
    cpp/collection/collectionmodel.cpp \
    cpp/user/profileModel.cpp \
    cpp/user/profileuser.cpp \
    cpp/collection/notes.cpp \
    cpp/wantlist/wants.cpp \
    cpp/wantlist/wantlistmodel.cpp \
    cpp/collection/fieldsmodel.cpp \
    cpp/collection/collectionsortmodel.cpp



RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    header/search/artist.h \
    header/search/label.h \
    header/search/master.h \
    header/search/images.h \
    header/search/members.h \
    header/search/release.h \
    header/search/artists.h \
    header/search/community.h \
    header/search/formats.h \
    header/search/identifiers.h \
    header/search/companies.h \
    header/search/tracklist.h \
    header/search/videos.h \
    header/search/users.h \
    header/search/raiting.h \
    header/search/searchmodel.h \
    header/system/o1.h \
    header/system/o1requestor.h \
    header/system/o2abstractstore.h \
    header/system/o2globals.h \
    header/system/o2replyserver.h \
    header/system/o2settingsstore.h \
    header/system/secureimageprovider.h \
    header/system/simplecrypt.h \
    header/system/verify.h \
    header/search/searchresult.h \
    header/system/qmltyperegistrator.h \
    header/collection/folders.h \
    header/collection/collectionreleases.h \
    header/search/sublabels.h \
    header/collection/basicinfo.h \
    header/collection/fields.h \
    header/collection/collectionmodel.h \
    header/user/profileModel.h \
    header/user/profileuser.h \
    header/collection/notes.h \
    header/collection/options.h \
    header/wantlist/wants.h \
    header/wantlist/wantlistmodel.h \
    header/collection/fieldsmodel.h \
    cpp/collection/collectionsortmodel.h \
    header/collection/collectionsortmodel.h
