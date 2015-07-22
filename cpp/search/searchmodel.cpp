#include <header/search/searchmodel.h>
#include <header/system/qmltyperegistrator.h>
#include <header/system/o2globals.h>

namespace {
QmlTypeRegistrator registrator(qmlRegisterType<SearchModel>("SearchModel",1,0,"SearchModel"));
}


SearchModel::SearchModel(QObject *parent)
    : QAbstractListModel(parent)
{

    qDebug() << "SearchModel constructor ";
    currentPage = 0;  // ничего не искали
    pagesInResult = 0; //количество страниц в результате поиска 0
    timeOut = 10000; // Таймаут при чтении данных по сети
    iWaitFirstSearch = false; // Ничего не ищем
    /*
    if (O1Requestor::instance().isLoggin())
    {
        m_wantResource = O1Requestor::instance().value("wantlist_url"); //Получится считать только для залогиненого пользователя
        m_collectionFolder = O1Requestor::instance().value("collection_folders_url");
        m_userName = O1Requestor::instance().value("username");
    }*/
    //   qDebug() << "OffLine Mode - " + QString(O1Requestor::instance().isOffline());


}

///*****************************************************************************************************************
void SearchModel::setFilterToSearch (const QString &s)
{
    iFilterToSearch = s;
}


///******************************************************************************************************************
void SearchModel::clear()
{
    //Тут удаляем ранее считанные данные о релизах в коллекции

    emit beginResetModel();
    m_SearchResult.clear();
    emit endResetModel();

}

///*****************************************************************************************************************

void SearchModel::search(QString searchBy)
{

    // Проверяем есть ли логин пользователя
 //   if(O1Requestor::instance().isLogging())
    if(true)
    {
        setWaitFirstSearch (true);

        if (!m_SearchResult.isEmpty())
        {
            qDebug() << "Clear m_Relaeses";

         clear();
            /*
            emit beginRemoveRows(QModelIndex(), 0, rowCount()-1);
            m_SearchResult.clear();
            emit endRemoveRows();
            */
        }
        // Пробуем работать не по oautch
        qDebug() << "Search by " + searchBy;
        QList<O1RequestParameter> reqParams = QList<O1RequestParameter>();
        reqParams << O1RequestParameter("q",searchBy.toUtf8());
        reqParams << O1RequestParameter("type",iFilterToSearch.toUtf8());         //Параметр поиска

        reqParams << O1RequestParameter("per_page", "50"); // Лучше задем вынести как опцию.
        reqParams << O1RequestParameter("key",O2_OAUTH2_CLIENT_ID);
        reqParams << O1RequestParameter("secret",O2_OAUTH2_CLIENT_SECRET);

        currentPage = 1;  //начинаем поиск
        QByteArray data = O1Requestor::instance().createQueryParams(reqParams);
        url = QUrl("https://api.discogs.com/database/search?"+data);

        getData();
        setWaitFirstSearch (false);
    }

}

/// *****************************************************************************************

bool SearchModel::waitFirstSearch () const
{
    return iWaitFirstSearch;
}
/// *****************************************************************************************

void SearchModel::setWaitFirstSearch (const bool &a)
{
    iWaitFirstSearch = a;
    emit waitFirstSearchChanged();

}



/// *****************************************************************************************
void SearchModel::readReleases(const int &index)
{

    QModelIndex i2 = createIndex(index,index);
    //Можно попробовать разделить чтение информации на 4 разные функции и вызывать каждую их них из своей вью
    bool result = false;

    if(!m_SearchResult[index].isLoading())
    {
       if(m_SearchResult[index].type() == "release")
               { result = getInfoForRelease(index);}
       else if(m_SearchResult[index].type() == "master")
               { result = getInfoForMaster(index);}
       else if (m_SearchResult[index].type() == "artist")
               {result = getInfoForArtist(index);}
       else if (m_SearchResult[index].type() == "label")
               {result = getInfoForLabel(index);}
     }
         m_SearchResult[index].setIsLoading(result);
        emit dataChanged(i2,i2);

 //        return result;
}


/// *****************************************************************************************
bool SearchModel::canFetchMore(const QModelIndex &parent) const
{

    if (parent.isValid())
    {
        return false;
    }  else if (waitFirstSearch())
    {
        return false;
    } else return currentPage < pagesInResult ? true : false;


}
///*******************************************************************************************


void SearchModel::fetchMore(const QModelIndex &parent)
{
    if (!parent.isValid())
    {

        getData();

    }
}

///********************************************************************************************************



bool SearchModel::addReleasesInWantlist(const int &index)
{
    QString strReply;
    QByteArray data;
    QModelIndex i2 = createIndex(index,index);

    //в WantList могут быть добавлены объекты Master и Релиз. При добавлении для релиза могуть быть указан рейтинг и note через параметры запроса

    QNetworkRequest request(QUrl(O1Requestor::instance().value("wantlist_url") + "/" + QString::number(m_SearchResult[index].release().id())));
    if (!O1Requestor::instance().putWithWait(request, data, timeOut))
    {
        qDebug() << "ERROR add releases to WantList: ";
        qDebug() << strReply;
        return false;

    } else {
        qDebug() << "Release add to WantList: ";
        m_SearchResult[index].setIsInWl(true);
        emit dataChanged(i2,i2);
        emit addReleasesToWantlist();
        return true;
    }
}


///********************************************************************************************************



bool SearchModel::addReleasesInCollection(const int &index)
{
    QString strReply;
    QByteArray dataNull;
    QModelIndex i2 = createIndex(index,index);

 // по умолчанию добавляем в каталог Uncategorized - 1
    QNetworkRequest request(QUrl(O1Requestor::instance().value("collection_folders_url") + "/1/releases/" + QString::number(m_SearchResult[index].release().id())));

    if (!O1Requestor::instance().postWithWait(request, dataNull, strReply, timeOut))
    {

        qDebug() << "ERROR add releases to WantList: ";
        qDebug() << strReply;
  //      result = strReply;                    // Для обозначения ошибки пользователю
        return false;

    } else {
        qDebug() << "Release add to Collection: ";
        qDebug() << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        //Для записи в списке результатов поиска сохраняем строку о добавлении этой записи в коллекцию и признак
        m_SearchResult[index].setResourceUrlInCollection(jsonObj["resource_url"].toString());
        m_SearchResult[index].setInstanceInCollection(jsonObj["instance_id"].toInt());
        m_SearchResult[index].setIsInCl(true);


        //нужно еще  перерисовать вью для релиза в списке найденных записей и вью wantlista
        emit dataChanged(i2,i2);
        emit addReleasesToCollection();
        return true;
    }


}

///********************************************************************************************************

bool SearchModel::editReleasesInWantlist(const int &index, const QString &notes)
{
    //Сделать по аналогии с добавлением в коллекцию
    QString strReply;

    QModelIndex i2 = createIndex(index,index);
    //Редактирование записи в wantlist после добавления
        QJsonObject array;
        array.insert(QString("username"),QJsonValue(O1Requestor::instance().value("username")));
        array.insert(QString("notes"),QJsonValue(notes));
        QJsonDocument param = QJsonDocument(array);

        QNetworkRequest request(QUrl(O1Requestor::instance().value("wantlist_url") + "/" + QString::number(m_SearchResult[index].release().id())));
        if (!O1Requestor::instance().postWithWait(request, param.toJson(),strReply, timeOut))
        {

            qDebug() << "ERROR edit to wantlist witch notes ";
            return false;

        }
        qDebug() << strReply;
        emit dataChanged(i2,i2);
        emit editReleasesToWantlist();
        return true;

}

///********************************************************************************************************

bool SearchModel::editReleasesInWantlist(const int &index, const int &rating)
{
    //Сделать по аналогии с добавлением в коллекцию
    QString strReply;

    QModelIndex i2 = createIndex(index,index);
    //Редактирование записи в wantlist после добавления
        QJsonObject array;
        array.insert(QString("username"),QJsonValue(O1Requestor::instance().value("username")));
        array.insert(QString("rating"),QJsonValue(rating));
        QJsonDocument param = QJsonDocument(array);

        QNetworkRequest request(QUrl(O1Requestor::instance().value("wantlist_url") + "/" + QString::number(m_SearchResult[index].release().id())));
        if (!O1Requestor::instance().postWithWait(request, param.toJson(),strReply, timeOut))
        {

            qDebug() << "ERROR edit to wantlist witch notes ";
            return false;

        }
        qDebug() << strReply;
        emit dataChanged(i2,i2);
        emit editReleasesToWantlist();
        return true;

}
///********************************************************************************************************
bool SearchModel::editReleasesInCollection(const int &index, const int &rating,  const int &folderNumber)
{


    QString strReply;
    QModelIndex i2 = createIndex(index,index);
    QJsonObject array;

    QString str = m_SearchResult[index].resurceUrlInCollection();
    int i = str.indexOf("?");
    str = str.remove(i,(str.length() - i));            //Удаляем в строке все что идет после ?
    QNetworkRequest request(QUrl(str + "/instances/" + QString::number(m_SearchResult[index].instanceInCollection())));

  //  QNetworkRequest request(QUrl(m_SearchResult[index].resurceUrlInCollection()));
    array.insert(QString("username"),QJsonValue(O1Requestor::instance().value("username")));
    if (folderNumber>0){
        array.insert(QString("folder_id"),QJsonValue(folderNumber));}
    array.insert(QString("rating"),QJsonValue(rating));
    QJsonDocument param = QJsonDocument(array);
    //направляем первый запрос на редактирование двух параметров: рейтинг и каталог
    if (!O1Requestor::instance().postWithWait(request, param.toJson(),strReply, timeOut))
    {

        qDebug() << "ERROR edit collection ";
        return false;

    }
    qDebug() << strReply;
    //По идее нужно изменить resurceUrlInCollection, т.к. может измениться каталог, это уже актуально для модели коллекция
    emit dataChanged(i2,i2);
    emit editReleasesToCollection();
    return true;

}

bool SearchModel::editFieldsInCollection(const int &index,  const int &idFieldsToEdit, const QString &valueFieldToEdit)
{
    // Редактируем filds

    QString strReply;
    QModelIndex i2 = createIndex(index,index);
    QJsonObject array;
    QString str = m_SearchResult[index].resurceUrlInCollection();
    int i = str.indexOf("?");
    str = str.remove(i,(str.length() - i));            //Удаляем в строке все что идет после ?

    QNetworkRequest request(QUrl(str + "/instances/" + QString::number(m_SearchResult[index].instanceInCollection())+ "/fields/" +QString::number(idFieldsToEdit)));
    array.insert(QString("username"),QJsonValue(O1Requestor::instance().value("username")));
    array.insert(QString("value"),QJsonValue(valueFieldToEdit));
    QJsonDocument param = QJsonDocument(array);
    if (!O1Requestor::instance().postWithWait(request, param.toJson(),strReply, timeOut))
    {

        qDebug() << "ERROR edit collection ";
        return false;

    }
    qDebug() << strReply;
    emit dataChanged(i2,i2);
    emit addReleasesToCollection();
    return true;

}


///********************************************************************************************************

void SearchModel::getData()

{

        QNetworkRequest request(url);
        QString strReply;
 //       if (!O1Requestor::instance().getWithWaiting(request,strReply, timeOut))
        if (!O1Requestor::instance().getWithWaiting(request,strReply, timeOut))
        {
            qDebug() << "ERROR Search:";
        } else {


            qDebug() << "Search OK";
            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
            QJsonObject jsonObj = jsonResponse.object();

            qDebug() << "Search done in Json " <<jsonObj;
            QJsonObject pagination = jsonObj["pagination"].toObject();
            itemsInResult = pagination["items"].toInt();

            if (itemsInResult==0){

                qDebug() << "Not found ";

                //       return false;

            } else {

                pagesInResult = pagination["pages"].toInt();
                currentPage = pagination["page"].toInt();
                QJsonObject resultUrls = pagination["urls"].toObject();
                nextPageForSearh = resultUrls["next"].toString();
                url = QUrl(nextPageForSearh);
                QJsonArray result = jsonObj["results"].toArray();

                //Удаляем последнюю строчку
                if ((currentPage>1)&&(currentPage<=pagesInResult)) {
                    emit beginRemoveRows(QModelIndex(),rowCount()-1,rowCount()-1);
                    m_SearchResult.pop_back();
                    emit endRemoveRows();
                }
                //Добавляем данные
                emit beginInsertRows(QModelIndex(), rowCount(), rowCount()+result.size()-1);

                for (QJsonArray::const_iterator iter = result.begin();iter!= result.end(); ++iter)
                {

                    addSearchResult ((*iter).toObject());

                }
                m_SearchResult << SearchResult(true);  //добавляем запись с признаком тупилки

                emit endInsertRows();
                if (currentPage==pagesInResult) { //Если поиск завершен удаляем итем с тупилкой
                    emit beginRemoveRows(QModelIndex(),rowCount()-1,rowCount()-1);
                    m_SearchResult.pop_back();
                    emit endRemoveRows();
                }


            }

        }

}


void SearchModel::addSearchResult (const QJsonObject &o)
{
    // Переделать
    QString type;
    bool isMaster = false;
    bool isArtist = false;
    bool isRelease = false;
    bool isLabel = false;

 //   QString want;
 //   QString have;


    /*    Artist oneArtist;
    Release oneRelease;
    Master oneMaster;
    Label oneLabel;*/


    qDebug() << o;


    //   QJsonObject communityJSon = o["community"].toObject();

    type = o["type"].toString();
    if (type == "master")
        isMaster = true;
    else  if (type == "release")
        isRelease = true;
    else if (type == "artist")
        isArtist = true;
    else  if (type == "label")
        isLabel = true;


    //Добавлено для определения нахождения релиза или мастера в списках пользователя


    m_SearchResult << SearchResult(false,                            //  bool isDummy
                                   type,
                                   false,               //isLoading,
                                   isArtist,                // isArtist,
                                   isRelease,                // isRelease,
                                   isMaster,                //isMaster,
                                   isLabel,               // isLabel,
                                   fromjIterToString(o,QString("title")),
                                   o["thumb"].toString(),
            o["resource_url"].toString(),
            fromjIterToString(o,QString("label")),
            fromjIterToString(o,QString("format")),
            fromjIterToString(o,QString("country")),
            fromjIterToString(o,QString("year")),
            fromjIterToString(o,QString("catno")),
            fromjIterToString(o,QString("genre")),
            fromjIterToString(o,QString("style")));



}



///*******************************************************************************************************

QString SearchModel::fromjIterToString(const QJsonObject &o, const QString field)
{

    QJsonArray result= o[field].toArray();
    if (result.isEmpty())
    {
        //      qDebug() << o[field].toString();
        return o[field].toString();
    }
    else {
        return jArrayToString(result);
    }

}
///********************************************************************************************************
bool SearchModel::getInfoForArtist (const int &index)
{
        int i;
        QUrl u = QUrl(m_SearchResult[index].resourceUrl().toUtf8());
        QNetworkRequest request(u);
        QString strReply;

        if (!O1Requestor::instance().getWithWaiting(request,strReply, timeOut))
        {
            qDebug() << "ERROR GetInfoForArtist:";
            return false;
        } else {

            qDebug() << "Get info for Artist OK";
            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
            QJsonObject jsonObj = jsonResponse.object();
            qDebug() << "JSONOBJ" << jsonObj;

            QJsonArray namevariations = jsonObj["namevariations"].toArray();
            qDebug() << "namevariations " << namevariations;
            QList<QString> i_namevariations;

            for (i=0; i<namevariations.size();i++)
            {
                i_namevariations << namevariations.at(i).toString();
            }

            QJsonArray urls = jsonObj["urls"].toArray();
            qDebug() << "Urls " << urls;
            QList<QString> i_urls;

            for (i=0; i<urls.size();i++)
            {
                i_urls << urls.at(i).toString();
            }

            QJsonArray images = jsonObj["images"].toArray();
            qDebug() <<  images;
            QList<Images> i_images;

            for (QJsonArray::const_iterator iter = images.begin();iter!= images.end(); ++iter)
            {
                const QJsonObject o = (*iter).toObject();
                i_images << Images(o["height"].toInt(),
                        o["width"].toInt(),
                        o["resource_url"].toString(),
                        o["uri"].toString(),
                        o["uri150"].toString(),
                        o["type"].toString());
            }

            QJsonArray members = jsonObj["members"].toArray();
            qDebug() <<  members;
            QList<Members> i_members;

            for (QJsonArray::const_iterator iter = members.begin();iter!= members.end(); ++iter)
            {
                const QJsonObject o = (*iter).toObject();
                i_members << Members(o["active"].toBool(),
                        o["id"].toInt(),
                        o["name"].toString(),
                        o["resource_url"].toString());

            }

            Artist i_artist = Artist(i_namevariations,
                                     jsonObj["profile"].toString(),
                                     jsonObj["releases_url"].toString(),
                                     jsonObj["resource_url"].toString(),
                                     jsonObj["uri"].toString(),
                                     i_urls,
                                     jsonObj["data_qaulity"].toString(),
                                     jsonObj["id"].toInt(),
                                     i_images,
                                     i_members);



            m_SearchResult[index].setArtist(i_artist);

            return true;


       }


}

///********************************************************************************************************
bool SearchModel::getInfoForLabel (const int &index)
{
    int i;
    QUrl u = QUrl(m_SearchResult[index].resourceUrl().toUtf8());
    QNetworkRequest request(u);
    QString strReply;

    if (!O1Requestor::instance().getWithWaiting(request,strReply, timeOut))
    {
        qDebug() << "ERROR GetInfoForLabel:";
        return false;
    } else {

        qDebug() << "Get info for label OK";

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        qDebug() << "JSONOBJ" << jsonObj;

        QJsonArray sublabels = jsonObj["sublabels"].toArray();
        qDebug() << "Sublabels " << sublabels;

        QList<Companies> i_sublabels;

        for (QJsonArray::const_iterator iter = sublabels.begin();iter!= sublabels.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_sublabels << Companies(o["catno"].toString(),
                    o["entity_type"].toString(),
                    o["entity_type_name"].toString(),
                    o["id"].toInt(),
                    o["name"].toString(),
                    o["resource_url"].toString());

        }

        QJsonArray urls = jsonObj["urls"].toArray();
        qDebug() << "Urls " << urls;
        QList<QString> i_urls;

        for (i=0; i<urls.size();i++)
        {
            i_urls << urls.at(i).toString();
        }

        QJsonArray images = jsonObj["images"].toArray();
        qDebug() <<  images;
        QList<Images> i_images;

        for (QJsonArray::const_iterator iter = images.begin();iter!= images.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_images << Images(o["height"].toInt(),
                    o["width"].toInt(),
                    o["resource_url"].toString(),
                    o["uri"].toString(),
                    o["uri150"].toString(),
                    o["type"].toString());
        }

        Label i_label = Label  (jsonObj["profile"].toString(),
                                jsonObj["releases_url"].toString(),
                                jsonObj["name"].toString(),
                                jsonObj["contact_info"].toString(),
                                jsonObj["uri"].toString(),
                                i_sublabels,
                                i_urls,
                                i_images,
                                jsonObj["resource_url"].toString(),
                                jsonObj["data_qaulity"].toString(),
                                jsonObj["id"].toInt());

        m_SearchResult[index].setLabel(i_label);


         return true;

    }


}


///********************************************************************************************************

bool SearchModel::getInfoForMaster (const int &index)
{
    int i;
    QUrl u = QUrl(m_SearchResult[index].resourceUrl().toUtf8());
    QNetworkRequest request(u);
    QString strReply;

    if (!O1Requestor::instance().getWithWaiting(request,strReply, timeOut))
    {
        qDebug() << "ERROR GetInfoForMaster:";
        return false;
    } else {


        qDebug() << "Get info for master OK";

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        qDebug() << "JSONOBJ" << jsonObj;

        QJsonArray styles = jsonObj["styles"].toArray();
        qDebug() << "Styles " << styles;
        QList<QString> i_styles;

        for (i=0; i<styles.size();i++)
        {
            i_styles << styles.at(i).toString();
        }

        QJsonArray genres = jsonObj["genres"].toArray();
        qDebug() << "Genres " << genres;
        QList<QString> i_genres;

        for (i=0; i<genres.size();i++)
        {
            i_genres << genres.at(i).toString();
        }

        QJsonArray videos = jsonObj["videos"].toArray();
        qDebug() << "Videos " << videos;
        QList <Videos>  i_videos;

        for (QJsonArray::const_iterator iter = videos.begin();iter!= videos.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_videos << Videos(o["description"].toString(),
                    o["duration"].toInt(),
                    o["embed"].toBool(),
                    o["title"].toString(),
                    o["uri"].toString());

        }

        QJsonArray artists = jsonObj["artists"].toArray();
        qDebug() <<  "artists " << artists;
        QList<Artists> i_artists;

        for (QJsonArray::const_iterator iter = artists.begin();iter!= artists.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_artists << Artists(o["anv"].toString(),
                    o["id"].toInt(),
                    o["join"].toString(),
                    o["name"].toString(),
                    o["resource_url"].toString(),
                    o["role"].toString(),
                    o["tracks"].toString());
        }

        QJsonArray images = jsonObj["images"].toArray();
        qDebug() <<  images;
        QList<Images> i_images;

        for (QJsonArray::const_iterator iter = images.begin();iter!= images.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_images << Images(o["height"].toInt(),
                    o["width"].toInt(),
                    o["resource_url"].toString(),
                    o["uri"].toString(),
                    o["uri150"].toString(),
                    o["type"].toString());
        }

        QJsonArray tracklist = jsonObj["tracklist"].toArray();
        qDebug() << "Tracklist " <<  tracklist;
        QList<Tracklist> i_tracklist;

        QJsonArray extraartists2; // = tracklist["extraartists"].toArray();

        QList<Artists>  i_extraartists2;

        for (QJsonArray::const_iterator iter = tracklist.begin();iter!= tracklist.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            extraartists2 = o["extraartists"].toArray();
            qDebug() << "Extraartists " << extraartists2;
            for (QJsonArray::const_iterator iter = extraartists2.begin();iter!= extraartists2.end(); ++iter)
            {
                const QJsonObject a = (*iter).toObject();
                i_extraartists2 << Artists(a["anv"].toString(),
                        a["id"].toInt(),
                        a["join"].toString(),
                        a["name"].toString(),
                        a["resource_url"].toString(),
                        a["role"].toString(),
                        a["tracks"].toString());
            }


            i_tracklist << Tracklist(o["duration"].toString(),
                    i_extraartists2,
                    o["position"].toString(),
                    o["title"].toString(),
                    o["type_"].toString());

            i_extraartists2.clear();


        }

        Master i_master = Master(i_styles,
                                 i_genres,
                                 i_videos,
                jsonObj["title"].toString(),
                jsonObj["main_release"].toInt(),
                jsonObj["main_release_url"].toString(),
                i_artists,
                jsonObj["versions_url"].toString(),
                jsonObj["year"].toInt(),
                i_images,
                jsonObj["resourceUrl"].toString(),
                i_tracklist,
                jsonObj["id"].toInt(),
                jsonObj["data_quality"].toString());


        m_SearchResult[index].setMaster(i_master);
   //     m_SearchResult[index].setIsLoading(true);
        return true;


    }


}

///********************************************************************************************************

bool SearchModel::getInfoForRelease (const int &index)
{

    int i;

    QUrl u = QUrl(m_SearchResult[index].resourceUrl().toUtf8());
    QNetworkRequest request(u);
    QString strReply;

    if (!O1Requestor::instance().getWithWaiting(request,strReply, timeOut))
    {
        qDebug() << "ERROR GetInfoForRelease:";
        return false;
    } else {


        qDebug() << "Get info for release OK";

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        qDebug() << "JSONOBJ" << jsonObj;

        QJsonArray artists = jsonObj["artists"].toArray();
        qDebug() <<  "artists " << artists;
        QList<Artists> i_artists;

        for (QJsonArray::const_iterator iter = artists.begin();iter!= artists.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_artists << Artists(o["anv"].toString(),
                    o["id"].toInt(),
                    o["join"].toString(),
                    o["name"].toString(),
                    o["resource_url"].toString(),
                    o["role"].toString(),
                    o["tracks"].toString());
        }

        QJsonObject community = jsonObj["community"].toObject();
        qDebug() << "Community " << community;
        Community i_community;
        QJsonArray contributors = community["contributors"].toArray();
        qDebug() << "Contributors " << contributors;
        QList<Users> i_contributors;
        QJsonObject rating = community["rating"].toObject();

        Raiting i_rating = Raiting(rating["avarage"].toInt(),
                rating["count"].toInt());

        QJsonObject submitter  = community["submitter"].toObject();

        Users i_submitters = Users(submitter["resource_url"].toString(),
                submitter["username"].toString());


        for (QJsonArray::const_iterator iter = contributors.begin();iter!= contributors.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_contributors << Users(o["resource_url"].toString(),
                    o["username"].toString());
        }


        i_community = Community(i_contributors,
                                community["data_quality"].toString(),
                community["have"].toInt(),
                i_rating,
                community["status"].toString(),
                i_submitters,
                community["want"].toInt());




        QJsonArray companies = jsonObj["companies"].toArray();
        qDebug() << "Companies " << companies;

        QList<Companies> i_companies;

        for (QJsonArray::const_iterator iter = companies.begin();iter!= companies.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_companies << Companies(o["catno"].toString(),
                    o["entity_type"].toString(),
                    o["entity_type_name"].toString(),
                    o["id"].toInt(),
                    o["name"].toString(),
                    o["resource_url"].toString());

        }



        QJsonArray extraartists = jsonObj["extraartists"].toArray();
        qDebug() << "Extraartists " << extraartists;
        QList<Artists>  i_extraartists;

        for (QJsonArray::const_iterator iter = extraartists.begin();iter!= extraartists.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_extraartists << Artists(o["anv"].toString(),
                    o["id"].toInt(),
                    o["join"].toString(),
                    o["name"].toString(),
                    o["resource_url"].toString(),
                    o["role"].toString(),
                    o["tracks"].toString());
        }

        QJsonArray formats = jsonObj["formats"].toArray();
        qDebug() << "Formats " <<  formats;
        QList<Formats>  i_formats;

        for (QJsonArray::const_iterator iter = formats.begin();iter!= formats.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            QJsonArray descriptions = o["descriptions"].toArray();  //изменено
            qDebug() << "Descriptions " << descriptions ;
            QList<QString> i_descriptions;

            for (i=0; i<descriptions.size();i++)
            {
                i_descriptions << descriptions.at(i).toString();
            }

            i_formats << Formats(i_descriptions,
                                 o["name"].toString(),
                    o["qty"].toString());
        }


        // const QList<QString> &description, const QString &name, const int &qty);



        QJsonArray genres = jsonObj["genres"].toArray();
        qDebug() << "Genres " << genres;
        QList<QString> i_genres;

        for (i=0; i<genres.size();i++)
        {
            i_genres << genres.at(i).toString();
        }


        QJsonArray identifiers = jsonObj["identifiers"].toArray();
        qDebug() << identifiers;
        QList<Identifiers> i_identifiers;
        for (QJsonArray::const_iterator iter2 = identifiers.begin();iter2!= identifiers.end(); ++iter2)
        {
            i_identifiers << Identifiers((*iter2).toObject()["type"].toString(),(*iter2).toObject()["value"].toString());
        }


        QJsonArray images = jsonObj["images"].toArray();
        qDebug() <<  images;
        QList<Images> i_images;

        for (QJsonArray::const_iterator iter = images.begin();iter!= images.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_images << Images(o["height"].toInt(),
                    o["width"].toInt(),
                    o["resource_url"].toString(),
                    o["uri"].toString(),
                    o["uri150"].toString(),
                    o["type"].toString());
        }


        QJsonArray labels = jsonObj["labels"].toArray();
        qDebug() << "Labels " << labels;
        QList<Companies> i_labels;

        for (QJsonArray::const_iterator iter = labels.begin();iter!= labels.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_labels << Companies(o["catno"].toString(),
                    o["entity_type"].toString(),
                    o["entity_type_name"].toString(),
                    o["id"].toInt(),
                    o["name"].toString(),
                    o["resource_url"].toString());

        }


        QJsonArray series = jsonObj["series"].toArray();
        qDebug() << "Series " << series;
        QList<QString> i_series;


        for (i=0; i<series.size();i++)
        {
            i_series << series.at(i).toString();
        }


        QJsonArray styles = jsonObj["styles"].toArray();
        qDebug() << "Styles " << styles;
        QList<QString> i_styles;

        for (i=0; i<styles.size();i++)
        {
            i_styles << styles.at(i).toString();
        }

        QJsonArray tracklist = jsonObj["tracklist"].toArray();
        qDebug() << "Tracklist " <<  tracklist;
        QList<Tracklist> i_tracklist;

        QJsonArray extraartists2; // = tracklist["extraartists"].toArray();

        QList<Artists>  i_extraartists2;

        for (QJsonArray::const_iterator iter = tracklist.begin();iter!= tracklist.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            extraartists2 = o["extraartists"].toArray();
            qDebug() << "Extraartists " << extraartists2;
            for (QJsonArray::const_iterator iter = extraartists2.begin();iter!= extraartists2.end(); ++iter)
            {
                const QJsonObject a = (*iter).toObject();
                i_extraartists2 << Artists(a["anv"].toString(),
                        a["id"].toInt(),
                        a["join"].toString(),
                        a["name"].toString(),
                        a["resource_url"].toString(),
                        a["role"].toString(),
                        a["tracks"].toString());
            }



            i_tracklist << Tracklist(o["duration"].toString(),
                    i_extraartists2,
                    o["position"].toString(),
                    o["title"].toString(),
                    o["type_"].toString());

            i_extraartists2.clear();


        }


        QJsonArray videos = jsonObj["videos"].toArray();
        qDebug() << "Videos " << videos;
        QList <Videos>  i_videos;

        for (QJsonArray::const_iterator iter = videos.begin();iter!= videos.end(); ++iter)
        {
            const QJsonObject o = (*iter).toObject();
            i_videos << Videos(o["description"].toString(),
                    o["duration"].toInt(),
                    o["embed"].toBool(),
                    o["title"].toString(),
                    o["uri"].toString());

        }

         qDebug() << "DateTime  " << jsonObj["date_added"] << " "  << jsonObj["date_changed"];

        Release i_release = Release(jsonObj["title"].toString(),                                     //title,
                jsonObj["id"].toInt(),                                                   //id
                i_artists,                                                                 //artists
                jsonObj["data_quality"].toString(),                                      //data_quality
                jsonObj["thumb"].toString(),                                             //thumb,
                i_community,
                i_companies,
                jsonObj["country"].toString(),
                QDateTime::fromString(jsonObj["date_added"].toString(),"yyyy-MM-ddThh:mm:ss"),
                QDateTime::fromString(jsonObj["date_changed"].toString(),"yyyy-MM-ddThh:mm:ss"),
                jsonObj["estimated_weight"].toString(),
                i_extraartists,          //класс для яэкстраартистов
                jsonObj["format_quantity"].toString(),
                i_formats,
                i_genres,
                i_identifiers,
                i_images,
                i_labels,
                jsonObj["master_id"].toInt(),
                jsonObj["master_url"].toString(),
                jsonObj["notes"].toString(),
                jsonObj["released"].toString(),
                jsonObj["released_formatted"].toString(),
                jsonObj["resourceUrl"].toString(),
                i_series,
                jsonObj["status"].toString(),
                i_styles,
                i_tracklist,
                jsonObj["uri"].toString(),
                i_videos,
                jsonObj["year"].toInt());

        m_SearchResult[index].setRelease(i_release);
  //      m_SearchResult[index].setIsLoading(true);
        return true;

    }

}



///********************************************************************************************************

QString SearchModel::jArrayToString(const QJsonArray &inputArray )
{
    QStringList sl;
    int i;

    for (i=0; i<inputArray.size();i++)
    {
        sl << inputArray.at(i).toString();
    }
    //    qDebug() << sl.join(", ");
    return sl.join(", ");

}


///*********************************************************************************************************

int SearchModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_SearchResult.count();
}

QVariant SearchModel::data(const QModelIndex & index, int role) const
{
    const int i = index.row();
    if (i < 0 || i >= m_SearchResult.count())
        return QVariant();
    if(!index.isValid())
        return QVariant();
  //   qDebug() << role << i;

     const SearchResult &oneSearchResult = m_SearchResult[i];

    switch(role)
    {
    case isDummy:
        return oneSearchResult.isDummy();
    case Type:
        return oneSearchResult.type();
    case isLoading:
        return oneSearchResult.isLoading();
    case isArtist:
        return oneSearchResult.isArtist();
    case isRelease:
        return oneSearchResult.isRelease();
    case isMaster:
        return oneSearchResult.isMaster();
    case isLabel:
        return oneSearchResult.isLabel();
    case Title:
        return oneSearchResult.title();
    case Thumb:
        return oneSearchResult.thumb();
    case ResourseUrl:
        return oneSearchResult.resourceUrl();
    case LabelShort:
        return oneSearchResult.labelshort();
    case Format:
        return oneSearchResult.format();
    case Country:
        return oneSearchResult.country();
    case Year:
        return oneSearchResult.year();
    case Catno:
        return oneSearchResult.catno();
    case Genre:
        return oneSearchResult.genre();
    case Style:
        return oneSearchResult.style();
    case ReleaseNotes:
        return oneSearchResult.release().notes();

    case ArtistNamevariations:
        return qlistToString(oneSearchResult.artist().namevariations());

    case ArtistProfiles:
        return oneSearchResult.artist().profiles();
    case ArtistUrls:
        return qlistToString(oneSearchResult.artist().urls());

    case LabelName:
        return oneSearchResult.label().name();
    case LabelProfiles:
        return oneSearchResult.label().profile();
    case LabelUrls:
        return qlistToString(oneSearchResult.label().urls());
    case InWL:
        return oneSearchResult.isInWl();
    case InCL:
        return oneSearchResult.isInCl();
    }

    return  QVariant();

}
/// ***********************************************************************************************************************
QString SearchModel::qlistToString(const QList<QString> & inpitList) const
{

    QStringList sl;
    int i;

    for (i=0; i<inpitList.size();i++)
    {
        sl << inpitList.at(i);
    }
   return sl.join(", ");


}


/// ***********************************************************************************************************************

QHash<int, QByteArray> SearchModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[isDummy] = "isDummy";
    roles[Type] = "Type";
    roles[isLoading] = "isLoading";
    roles[isArtist] = "isArtist";
    roles[isRelease] = "isRelease";
    roles[isMaster] = "isMaster";
    roles[isLabel] = "isLabel";
    roles[Title] = "Title";
    roles[Thumb] = "Thumb";
    roles[ResourseUrl] = "ResourseUrl";
    roles[LabelShort] = "LabelShort";
    roles[Format] = "Format";
    roles[Country] = "Country";
    roles[Year] = "Year";
    roles[Catno] = "Catno";
    roles[Genre] = "Genre";
    roles[Style] = "Style";

    roles[ReleaseNotes] = "ReleaseNotes";

    roles[ArtistNamevariations] = "ArtistNamevariations";
    roles[ArtistProfiles] = "ArtistProfiles";
    roles[ArtistUrls] = "ArtistUrls";

    roles[LabelName] = "LabelName";
    roles[LabelProfiles] = "LabelProfiles";
    roles[LabelUrls] = "LabelUrls";
    roles[InWL] = "InWL";
    roles[InCL] = "InCL";

    return roles;
}

///********************************************************************************************************************************

/*
QByteArray SearchModel::createQueryParams(const QList<O1RequestParameter> &params) {
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
*/
