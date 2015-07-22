#include <header/wantlist/Wantlistmodel.h>
#include <header/system/qmltyperegistrator.h>
#include <header/system/o2globals.h>



namespace {
QmlTypeRegistrator registrator(qmlRegisterType<WantlistModel>("WantlistModel",1,0,"WantlistModel"));
}



///******************************************************************************************************************
WantlistModel::WantlistModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qDebug() << "WantlistModel constructor ";
    setWaitReadWantlist(true);
 //   m_wantResource = O1Requestor::instance().value("wantlist_url");
    timeOut = 10000;                                                //Таймаут для запросов к сети
    //Пробуем считать по сети
    if (O1Requestor::instance().isLoggin())
    {
     getReleasesInWantList();
    }
//    if (!readOffLineWantList()) {  O1Requestor::instance().setIsOffline(false); emit isOfflineChanged();};
    setWaitReadWantlist(false);

}

///******************************************************************************************************************
WantlistModel::~WantlistModel()
{

}

///******************************************************************************************************************

void WantlistModel::refresh()
{
  setWaitReadWantlist(true);
  getReleasesInWantList();
  setWaitReadWantlist(false);
}

///******************************************************************************************************************
void WantlistModel::clear()
{

    emit beginResetModel();
    m_WantsResult.clear();
    emit endResetModel();

}

bool WantlistModel::waitReadWantlist() const
{
    return iWaitReadWantlist;

}

void WantlistModel::setWaitReadWantlist (const bool &a)
{
    iWaitReadWantlist = a;
    emit waitReadWantlistChanged();
}


///******************************************************************************************************************
bool WantlistModel::isOffline()
{
    return O1Requestor::instance().isOffline();
}


///*******************************************************************************************
void WantlistModel::getReleasesInWantList()
{
    QJsonArray fullResult;
    bool error = false;
    QNetworkRequest request;
    QString strReply;
    //Если уже список был сформирован, и не оффлайн то пока предлагаю его обнулить и считать заново

    if (!m_WantsResult.isEmpty())
    {
        qDebug() << "Clear and read again wantlist";
        clear();
    }

    if(O1Requestor::instance().isLoggin())
       {
        url = QUrl(O1Requestor::instance().value("wantlist_url"));
        request = QNetworkRequest(url);
         do {

            if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
                //           if (true) //Имитация ошибки чтения по сети
            {
                qDebug() << "ERROR get releases in WantList: ";
                error = true;                                           //ошибка при чтении по сети

            } else {

                qDebug() << "Get releases in Wantlist OK";

                QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
                QJsonObject jsonObj = jsonResponse.object();
                QJsonObject pagination = jsonObj["pagination"].toObject();
                itemsInResult = pagination["items"].toInt();
                pagesInResult = pagination["pages"].toInt();
                currentPage = pagination["page"].toInt();
                if (itemsInResult != 0)
                {
                    QJsonObject resultUrls = pagination["urls"].toObject();
                    nextPageForSearh = resultUrls["next"].toString();
                    url = QUrl(nextPageForSearh);

                    QJsonArray result = jsonObj["wants"].toArray();
                    qDebug() << "Releases in Json " <<result;
                    qDebug() << "Count releases " <<result.size();
                    if (result.size()>0)
                    {
                        //Добавляем данные
                        emit beginInsertRows(QModelIndex(), rowCount(), rowCount()+result.size()-1);

                        for (QJsonArray::const_iterator iter = result.begin();iter!= result.end(); ++iter)
                        {
                            const QJsonObject o = (*iter).toObject();
                            qDebug() << "Release " << o;
                            addResult (o);
                            fullResult.append(o);
                        }
                        emit endInsertRows();
                    }
                    request = QNetworkRequest(QUrl(url));
                }
            }
         }while((currentPage < pagesInResult)&&!error);

        if (!error)
        {
            //Пишем JSon в файл, если данные по сети были успешно считаны
            qDebug() << "Save Wantlist to file ";
            QFile wntlist(WANTLIST_FILENAME);
            if(!wntlist.open(QIODevice::WriteOnly))
            {
                qDebug() << "Couldn`t open  file to save";
            }
            else {
                QJsonDocument jsonToFile(fullResult);
                wntlist.write(jsonToFile.toJson());
                wntlist.close();
            }
        } else {
      //      O1Requestor::instance().setIsLoggin(false);
            if(!readOffLineWantList()) {O1Requestor::instance().setIsOffline(false); emit isOfflineChanged();}
         }
    } else
       {
        if(O1Requestor::instance().onlinked()) {
        if (!readOffLineWantList()) {O1Requestor::instance().setIsOffline(false); emit isOfflineChanged();} }
       }
}

///*******************************************************************************************
bool WantlistModel::readOffLineWantList()
{
    QFile wntlist(WANTLIST_FILENAME);
    if (wntlist.exists())                              //Если есть файл с данными, читаем из него
    {

        if(!wntlist.open(QIODevice::ReadOnly))
        {
            qDebug() << "Couldn`t open wantlistfile ";
            return false;
        } else
        {

            QByteArray saveData = wntlist.readAll();
            wntlist.close();
            QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
            QJsonArray result = loadDoc.array();
            qDebug() << "Releases in Json " <<result;
            if (result.size()>0)
            {
                emit beginInsertRows(QModelIndex(), rowCount(), rowCount()+result.size()-1);

                for (QJsonArray::const_iterator iter = result.begin();iter!= result.end(); ++iter)
                {
                    const QJsonObject o = (*iter).toObject();
                    //         qDebug() << "Release " << o;
                    addResult (o);
                }

                emit endInsertRows();
            }
            O1Requestor::instance().setIsOffline(true);            // Признак того что работаем в оффлайне
            emit isOfflineChanged();
            return true;
        }
    }
    return false;
}

///*******************************************************************************************
void WantlistModel::addResult (const QJsonObject &o)
{

    int i;

    QJsonObject basicInformation = o["basic_information"].toObject();
    qDebug() <<  "basic_information " << basicInformation;


    BasicInfo i_basicInformation;

    QJsonArray labels = basicInformation["labels"].toArray();
    qDebug() << "Labels " << labels;

    QList<Companies> i_labels;     //может быть список

    for (QJsonArray::const_iterator iter = labels.begin();iter!= labels.end(); ++iter)
    {
        const QJsonObject b = (*iter).toObject();
        i_labels << Companies(b["catno"].toString(),
                b["entity_type"].toString(),
                b["entity_type_name"].toString(),
                b["id"].toInt(),
                b["name"].toString(),
                b["resource_url"].toString());

    }

    QJsonArray formats = basicInformation["formats"].toArray();
    qDebug() << "Formats " <<  formats;
    Formats  i_formats;

    for (QJsonArray::const_iterator iter = formats.begin();iter!= formats.end(); ++iter)
    {
        const QJsonObject c = (*iter).toObject();
        QJsonArray descriptions = c["descriptions"].toArray();
        qDebug() << "Descriptions " << descriptions ;
        QList<QString> i_descriptions;

        for (i=0; i<descriptions.size();i++)
        {
            i_descriptions << descriptions.at(i).toString();
        }

        i_formats = Formats(i_descriptions,
                             c["name"].toString(),
                c["qty"].toString());
    }


    QJsonArray artists = basicInformation["artists"].toArray();
    qDebug() <<  "artists " << artists;
    Artists i_artists;

    for (QJsonArray::const_iterator iter = artists.begin();iter!= artists.end(); ++iter)
    {
        const QJsonObject d = (*iter).toObject();
        i_artists = Artists(d["anv"].toString(),
                d["id"].toInt(),
                d["join"].toString(),
                d["name"].toString(),
                d["resource_url"].toString(),
                d["role"].toString(),
                d["tracks"].toString());
    }


    QJsonArray notes = o["notes"].toArray();
    qDebug() <<  "notes " << notes;
    QList<Notes> i_notes;

    for (QJsonArray::const_iterator iter = notes.begin();iter!= notes.end(); ++iter)
    {
        const QJsonObject e = (*iter).toObject();
        i_notes << Notes(e["field_id"].toInt(), e["value"].toString());
    }


   i_basicInformation = BasicInfo(basicInformation["id"].toInt(),
            basicInformation["title"].toString(),
            basicInformation["year"].toInt(),
            basicInformation["resource_url"].toString(),
            basicInformation["thumb"].toString(),
            i_formats,
            i_labels,
            i_artists,
            i_notes);


    m_WantsResult << Wants(o["rating"].toInt(),
                           i_basicInformation,
                           o["resource_url"].toString(),
                           o["id"].toInt());


}
///*******************************************************************************************
bool WantlistModel::deleteReleaseFromWantlist(const int &index)
{

     QNetworkRequest request(QUrl(O1Requestor::instance().value("wantlist_url") + "/" + QString::number(m_WantsResult[index].id())));
     if (!O1Requestor::instance().deleteWithWait(request, timeOut))
     {
         qDebug() << "ERROR delete releases from WantList: ";
         return false;

     } else {
         qDebug() << "Release delete from WantList: ";
         //нужно еще удалить элемент в списке и перерисовать вью
         emit beginRemoveRows(QModelIndex(),index,index);
         m_WantsResult.removeAt(index);
         emit endRemoveRows();
         return true;
     }

}



///*******************************************************************************************
bool WantlistModel::canFetchMore(const QModelIndex &parent) const
{
      return false;

}
///*******************************************************************************************

void WantlistModel::fetchMore(const QModelIndex &parent)
{
    if (!parent.isValid())
    {

        //      getData(pagesAtNextSearch);

    }
}


///*********************************************************************************************************

int WantlistModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_WantsResult.count();
}
///*********************************************************************************************************

QVariant WantlistModel::data(const QModelIndex & index, int role) const
{
    const int i = index.row();
    if (i < 0 || i >= m_WantsResult.count())
        return QVariant();

    const Wants &oneWantsResult = m_WantsResult[i];

    switch(role)
    {
    case Title:
        return oneWantsResult.basicInformation().title();
    case Year:
        return oneWantsResult.basicInformation().year();
    case Thumb:
        return oneWantsResult.basicInformation().thumb();
    case FormatShort:
        return qlistToString(oneWantsResult.basicInformation().formats().description());
    case LabelShort:
        return labelNameToString(oneWantsResult.basicInformation().labels());  // предусмотреть возврат списка
    case Catno:
        return labelCatnoToString(oneWantsResult.basicInformation().labels());
    case ArtistName:
        return oneWantsResult.basicInformation().artists().name();
    case Rating:
        return oneWantsResult.rating();

    }
    return  QVariant();
}


/// ***********************************************************************************************************************

QHash<int, QByteArray> WantlistModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[Title] = "Title";
    roles[Year] = "Year";
    roles[Thumb] = "Thumb";
    roles[FormatShort] = "FormatShort";
    roles[LabelShort] = "LabelShort";
    roles[Catno] = "Catno";
    roles[ArtistName] = "ArtistName";
    roles[Rating] = "Rating";



    return roles;
}

/// ***********************************************************************************************************************
QString WantlistModel::labelNameToString(const QList<Companies> &companies) const
{
    QStringList sl;
    QList<Companies>::const_iterator i;
       for (i=companies.begin();i!=companies.end();++i)
       {
            sl << (*i).name();
       }
       return sl.join(", ");

}

/// ***********************************************************************************************************************
QString WantlistModel::labelCatnoToString(const QList<Companies> &companies) const
{
    QStringList sl;
    QList<Companies>::const_iterator i;
       for (i=companies.begin();i!=companies.end();++i)
       {
            sl << (*i).catno();
       }
       return sl.join(", ");

}
/// ***********************************************************************************************************************

QString WantlistModel::qlistToString(const QList<QString> & inputList) const
{

    QStringList sl;
    int i;

    for (i=0; i<inputList.size();i++)
    {
        sl << inputList.at(i);
    }
   return sl.join(", ");

}
