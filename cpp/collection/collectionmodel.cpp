#include "header/collection/collectionmodel.h"
#include <header/system/qmltyperegistrator.h>
#include <header/system/o2globals.h>
#include <header/collection/collectionsortmodel.h>



namespace {
QmlTypeRegistrator registrator(qmlRegisterType<CollectionModel>("CollectionModel",1,0,"CollectionModel"));
}


CollectionModel::CollectionModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qDebug() << "CollectionModel constructor ";

    timeOut = 10000;
    progressValue_=0;



     setWaitReadCollection(false);
 //    m_isNotEmpty = false;
     if (O1Requestor::instance().isLoggin())
     {
 //    m_userResource = O1Requestor::instance().value("resource_url");
//     rowReleasesInCollection = O1Requestor::instance().value("num_collection").toInt();
     getFoldersInCollection();                     //вынес в конструктор, т.к. данный о каталог нужны сразу же на вью
     getReleasesInCollection();                    //читаем коллекцию (онлайн, либо из файла) можно убрать для скорости загрузки
     setWaitReadCollection(false);
    }


//     m_sortFilterProxyModel = new CollectionSortModel();
//     m_sortFilterProxyModel.setSourceModel(this);
//     m_sortFilterProxyModel.setDynamicSortFilter(true);
 //    m_sortFilterProxyModel.setFilterRole(Title);
 //    m_sortFilterProxyModel.setFilterWildcard("Pink");

   //  m_sortFilterProxyModel->setDynamicSortFilter(true);
   //  m_sortFilterProxyModel->sort(0);
     //    m_sortFilterProxyModel->invalidate();
     //    m_sortFilterProxyModel->setFilterFixedString("pink");
}

///******************************************************************************************************************
void CollectionModel::refreshFilter()
{
//    m_sortFilterProxyModel.invalidate();
}

///*******************************************************************************************
void CollectionModel::clear()
{
    //Тут удаляем ранее считанные данные о релизах в коллекции
    emit beginResetModel();
    f_CollectionResult.clear();
    emit endResetModel();
    m_Folders.clear();
    m_CollectionResult.clear();

    emit folderRead();

}


///*******************************************************************************************
void CollectionModel::refresh()
{
  //    m_isNotEmpty = false;

    //Если уже список был сформирован, и не оффлайн то пока предлагаю его обнулить и считать заново
       setWaitReadCollection(true);
        if (!f_CollectionResult.isEmpty())
        {
           clear();
        }
        if (m_Folders.count()==0) {
            getFoldersInCollection(); emit folderRead();}
    //  emit isNotEmptyChanged();
      getReleasesInCollection();
      setWaitReadCollection(false);
}

///*******************************************************************************************
int CollectionModel::folderCount()
{
   return m_Folders.count();
}
///*******************************************************************************************
int CollectionModel::fieldCount()
{
    return m_Fields.count();   //не все так просто, количество списков может быть разным, как и количество записей в списках
}

///*******************************************************************************************
int CollectionModel::getCountOptionsOfField(const int &i)
{
    return m_Fields[i].options().count();
}
///*******************************************************************************************

QString CollectionModel::getOptionsInField(const int &i,const int &n)
{
 return m_Fields[i].options()[n];
}


///*******************************************************************************************
QString CollectionModel::folderName (const int &i)
{
   return m_Folders[i].name();
}
///*******************************************************************************************
int CollectionModel::folderId (const int &i)
{
   return m_Folders[i].id();
}

///*******************************************************************************************
void CollectionModel::setFolderFilter (const int &i)
{
    int j;

    if (!m_CollectionResult.isEmpty())              //Если оригинал коллекции не пустой
    {
        setWaitReadCollection(true);
        emit beginResetModel();
        f_CollectionResult.clear();                 //очищаем копию.
        if (i==0)                                   //Если ALL, тупо копируем
        {
            f_CollectionResult = m_CollectionResult;
        } else
        {
            for (j=0; j<m_CollectionResult.size(); j++)
            {
     //           qDebug() << m_CollectionResult[j].folder_id();
                if (m_CollectionResult[j].folder_id()==i)            //Если id записи совпадает в выбранным в фильтре, строим новый список
                {
                    f_CollectionResult << m_CollectionResult[j];
                }
            }

        }
        emit endResetModel();
        setWaitReadCollection(false);
    }

    //  ifolderIdToFilter = i;
}

///*******************************************************************************************
bool CollectionModel::lessThanTitle(const CollectionReleases &s1, const CollectionReleases &s2)           //сравнивает две строки без учета регистра
{
    return s1.basicInformation().title().compare(s2.basicInformation().title(),Qt::CaseInsensitive) <0;

  //  return s1.basicInformation().title().toLower() < s2.basicInformation().title().toLower();
}
///*******************************************************************************************
bool CollectionModel::lessThanArtist(const CollectionReleases &s1, const CollectionReleases &s2)           //сравнивает две строки без учета регистра
{
    return s1.basicInformation().artists().name().compare(s2.basicInformation().artists().name(),Qt::CaseInsensitive) <0;
}
///*******************************************************************************************
bool CollectionModel::lessThanRating(const CollectionReleases &s1, const CollectionReleases &s2)           //сравнивает два числа
{
    return s1.rating() < s2.rating();
}
///*******************************************************************************************

bool CollectionModel::lessThanFormat(const CollectionReleases &s1, const CollectionReleases &s2)
{

    QList<QString> r1 = s1.basicInformation().formats().description();
    QList<QString> r2 = s2.basicInformation().formats().description();

    QStringList sl1,sl2;
    int i;

    for (i=0; i<r1.size();i++)
    {
        sl1 << r1.at(i);
    }
    sl1.join(", ");

    for (i=0; i<r2.size();i++)
    {
        sl2 << r2.at(i);
    }
    return sl1.join(", ").compare(sl2.join(", "),Qt::CaseInsensitive) <0;

}

///*******************************************************************************************
bool CollectionModel::lessThanLabel(const CollectionReleases &s1, const CollectionReleases &s2)
{
    QList<Companies> r1 = s1.basicInformation().labels();
    QList<Companies> r2 = s2.basicInformation().labels();
    QStringList sl1, sl2;
    QList<Companies>::const_iterator i;

       for (i=r1.begin();i!=r1.end();++i)
       {
            sl1 << (*i).name();
       }

       for (i=r2.begin();i!=r2.end();++i)
       {
            sl2 << (*i).name();
       }
     return sl1.join(", ").compare(sl2.join(", "),Qt::CaseInsensitive) <0;


}

///*******************************************************************************************
bool CollectionModel::lessThanYear(const CollectionReleases &s1, const CollectionReleases &s2)
{
    return s1.basicInformation().year() < s2.basicInformation().year();
}
///*******************************************************************************************

bool CollectionModel::lessThanCatalog(const CollectionReleases &s1, const CollectionReleases &s2)
{
    QList<Companies> r1 = s1.basicInformation().labels();
    QList<Companies> r2 = s2.basicInformation().labels();
    QStringList sl1, sl2;
    QList<Companies>::const_iterator i;

       for (i=r1.begin();i!=r1.end();++i)
       {
            sl1 << (*i).catno();
       }

       for (i=r2.begin();i!=r2.end();++i)
       {
            sl2 << (*i).catno();
       }
     return sl1.join(", ").compare(sl2.join(", "),Qt::CaseInsensitive) <0;
}


///*******************************************************************************************
void CollectionModel::sortBy (const QString &param)
{
    setWaitReadCollection(true);
    if (!m_CollectionResult.isEmpty())              //Если оригинал коллекции не пустой
     {
        emit beginResetModel();
        if (param == "Title")                      // Сортируем по рейтингу
        {
        qSort(f_CollectionResult.begin(),f_CollectionResult.end(), lessThanTitle);
        } else if (param == "Artist")
        {
          qSort(f_CollectionResult.begin(),f_CollectionResult.end(), lessThanArtist);
        } else if (param == "Rating")
        {
          qSort(f_CollectionResult.begin(),f_CollectionResult.end(), lessThanRating);
        } else if (param == "Format")
        {
          qSort(f_CollectionResult.begin(),f_CollectionResult.end(), lessThanFormat);
        } else if (param == "Year")
        {
          qSort(f_CollectionResult.begin(),f_CollectionResult.end(), lessThanYear);
        } else if (param == "Label")
        {
          qSort(f_CollectionResult.begin(),f_CollectionResult.end(), lessThanLabel);
        } else if (param == "Catalog")
        {
          qSort(f_CollectionResult.begin(),f_CollectionResult.end(), lessThanCatalog);
        }
        emit endResetModel();
        setWaitReadCollection(false);
    }

}

///*******************************************************************************************

void CollectionModel::search (const QString &param)
{
    QList<int> result;        //Итоговый список индексов для результата
    int i;

    //Ищем не в пустом списке
    if (!m_CollectionResult.isEmpty())
    {

        setWaitReadCollection(true);
        emit beginResetModel();
        f_CollectionResult.clear();
        //Первоначально ищем по Кат. номеру
        if (!searchCatno(param))
        {
            //Если ничего не нашли, можно даже если нашли
            searchOtcher(param);                //Поиск по артисту,названию, году
        }
    }
    emit endResetModel();
    setWaitReadCollection(false);

}
//Функции поиска
///*******************************************************************************************
///По каталожному номеру
///
bool CollectionModel::searchCatno(const QString & param)
{
    QList<CollectionReleases>::const_iterator i;
    QList<Companies>::const_iterator j;
    QList<Companies> c;
    bool a = false;


    for (i = m_CollectionResult.begin(); i!=m_CollectionResult.end(); ++i)
    {
        c = (*i).basicInformation().labels();
        for (j = c.begin();j!=c.end();++j)
        {
            if ((*j).catno().contains(param,Qt::CaseInsensitive)||
                    (*j).name().contains(param,Qt::CaseInsensitive))
            {
                if(!checkInList(i))
                {
                    f_CollectionResult.append((*i));
                    a= true;
                }
            }
        }
    }

    return a;
}
/*
///*******************************************************************************************
///По Артисту

void CollectionModel::searchArtistTitleYear(const QString & param)
{
    QList<CollectionReleases>::const_iterator i;

    for (i = m_CollectionResult.begin(); i!=m_CollectionResult.end(); ++i)
    {
        if ((*i).basicInformation().artists().name().contains(param,Qt::CaseInsensitive)||
             (*i).basicInformation().title().contains(param,Qt::CaseInsensitive)||
             QString::number((*i).basicInformation().year()).contains(param,Qt::CaseInsensitive))
        {
            if(!checkInList(i))
            {
                f_CollectionResult.append(*i);
            }
        }
    }
}
*/
///*******************************************************************************************
///По остальным параметрам

void CollectionModel::searchOtcher(const QString & param)
{
    QList<CollectionReleases>::const_iterator i;
    QList<Notes>::const_iterator j;

    QList <Notes> c;

    bool found;

    for (i = m_CollectionResult.begin(); i!=m_CollectionResult.end(); ++i)
    {
        found = false;
        if ((*i).basicInformation().artists().name().contains(param,Qt::CaseInsensitive)||
             (*i).basicInformation().title().contains(param,Qt::CaseInsensitive)||
             QString::number((*i).basicInformation().year()).contains(param,Qt::CaseInsensitive))
        {
            found = true;                                                                             //Поиск по значениям в строках первого уровня
        } else              //Если не нашли по строкам первого уровня
        {
            c = (*i).basicInformation().notes();
            for (j = c.begin();j!=c.end();++j)
            {
                if((*j).value().contains(param,Qt::CaseInsensitive))
                {
                   found = true;
                }
            }

        }if(found && !checkInList(i))
        {
            f_CollectionResult.append(*i);
        }

    }
}


///*******************************************************************************************
///По Title
///
/*
void CollectionModel::searchTitle(const QString & param)
{
    QList<CollectionReleases>::const_iterator i;


    for (i = m_CollectionResult.begin(); i!=m_CollectionResult.end(); ++i)
    {
        if ((*i).basicInformation().title().contains(param,Qt::CaseInsensitive))
        {
            if(!checkInList(i))
            {
                f_CollectionResult.append(*i);
            }
        }
    }

}

///*******************************************************************************************
///По Словам в треке и Описании
///
void CollectionModel::searchNotes(const QString & param)
{
    QList<CollectionReleases>::const_iterator i;
    QList<Notes>::const_iterator j;

    QList <Notes> c;


    for (i = m_CollectionResult.begin(); i!=m_CollectionResult.end(); ++i)
    {
        c = (*i).basicInformation().notes();
        for (j = c.begin();j!=c.end();++j)
        {
            if((*j).value().contains(param,Qt::CaseInsensitive))
            {
                if(!checkInList(i))
                {
                    f_CollectionResult.append(*i);
                }
            }
        }
    }

}
*/
///*******************************************************************************************
bool CollectionModel::checkInList(QList<CollectionReleases>::const_iterator i)
{
  QList<CollectionReleases>::const_iterator j;
  bool a=false;

  for (j = f_CollectionResult.begin(); j!=f_CollectionResult.end(); ++j)
  {
      if ((*i).id()==(*j).id())
      {
          a=true;
      }
  }
   return a;

}

///*******************************************************************************************
bool CollectionModel::isNotEmpty()
{
    return m_isNotEmpty;
}

///*******************************************************************************************
bool CollectionModel::waitReadCollection() const
{
    return iwaitReadCollection;
}

///*******************************************************************************************
void CollectionModel::setWaitReadCollection(const bool &a)
{
    iwaitReadCollection = a;
    emit waitReadCollectionChanged();
}


///******************************************************************************************************************
bool CollectionModel::isOffline()
{
    return O1Requestor::instance().isOffline();
}

///******************************************************************************************************************
float CollectionModel::progressValue()
{
    return progressValue_;
}


///*******************************************************************************************
void CollectionModel::getFoldersInCollection()

{
    QJsonArray fullResult;
    bool error = false;
    QNetworkRequest request;

    if(O1Requestor::instance().isLoggin())
    {
        request = QNetworkRequest(QUrl(O1Requestor::instance().value("collection_folders_url")));
        QString strReply;
        if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
        {
            qDebug() << "ERROR get Collection:";
            error = true;
            //признак что ошибка при чтении коллекции
        } else {

            qDebug() << "Get Folder collection OK";
            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
            QJsonObject jsonObj = jsonResponse.object();
            QJsonArray folders = jsonObj["folders"].toArray();
            qDebug() << "Collection in Json " <<jsonObj;

            for (QJsonArray::const_iterator iter = folders.begin(); iter!= folders.end(); ++iter)
            {

                const QJsonObject o = (*iter).toObject();
                m_Folders << Folders(o["id"].toInt(),
                        o["count"].toInt(),
                        o["name"].toString(),
                        o["resource_url"].toString());
         //       if (o["id"].toInt()==0) { ifolderALLIdToFilter = m_Folders.size()-1;}             //Сохраняем индекс записи с id=0 папка ALL
                fullResult.append(o);
            }
        }
        if (!error)
        {
            //Пишем JSon в файл, если данные по сети были успешно считаны
            qDebug() << "Save folder to file ";

            QFile collection(FOLDER_FILENAME);
            if(!collection.open(QIODevice::WriteOnly))
            {
                qDebug() << "Couldn`t open  file to save";

            }
            else {
                QJsonDocument jsonToFile(fullResult);
                collection.write(jsonToFile.toJson());
                collection.close();
            }
        } else {
      //      O1Requestor::instance().setIsLoggin(false);
            if (!readOffLineFolder()) {O1Requestor::instance().setIsOffline(false);  emit isOfflineChanged();};
        }
    } else
    {
        if(O1Requestor::instance().onlinked()) {
            if(!readOffLineFolder()) {O1Requestor::instance().setIsOffline(false);  emit isOfflineChanged();} }
    }

}

bool CollectionModel::readOffLineFolder()
{

    QFile folder(FOLDER_FILENAME);
    if (folder.exists())                              //Если есть файл с данными, читаем из него
    {

        if(!folder.open(QIODevice::ReadOnly))
        {
            qDebug() << "Couldn`t open folderfile ";
            return false;
        } else
        {

            QByteArray saveData = folder.readAll();
            folder.close();
            QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
            QJsonArray result = loadDoc.array();
            qDebug() << "folder in Json " <<result;
          for (QJsonArray::const_iterator iter = result.begin();iter!= result.end(); ++iter)
            {
                const QJsonObject o = (*iter).toObject();
                m_Folders << Folders(o["id"].toInt(),
                        o["count"].toInt(),
                        o["name"].toString(),
                        o["resource_url"].toString());
      //          if (o["id"].toInt()==0) { ifolderALLIdToFilter = o["id"].toInt();}             //Сохраняем индекс записи с id=0 папка ALL
            }
            O1Requestor::instance().setIsOffline(true);            // Признак того что работаем в оффлайне
            emit isOfflineChanged();
            return true;
        }
    }
    return false;
}

///*******************************************************************************************
/*
void CollectionModel::getFilds()
{
    int i;
    QNetworkRequest request(QUrl(O1Requestor::instance().value("collection_fields_url")));
    QString strReply;
    if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
    {
        qDebug() << "ERROR get Fields:";

    } else {

        qDebug() << "Get Fields collection OK";
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        QJsonArray fields = jsonObj["fields"].toArray();
        qDebug() << "Fields in Json " <<jsonObj;

        for (QJsonArray::const_iterator iter = fields.begin(); iter!= fields.end(); ++iter)
        {

            const QJsonObject o = (*iter).toObject();

            QJsonArray options = o["options"].toArray();
            QList<QString> i_options;

            for (i=0; i<options.size();i++)
            {
                i_options << options.at(i).toString();
            }

            m_Fields << Fields(o["name"].toString(),
                    i_options,
                    o["id"].toInt(),
                    o["position"].toInt(),
                    o["type"].toString(),
                    o["public"].toBool(),
                    o["lines"].toInt());

        }


    }

}
*/
///*******************************************************************************************
void CollectionModel::getReleasesInCollection()
{


    QString m_instance;
    QString m_release;
    QString m_folder;
    QString strReply;
    QJsonArray fullResult;
    bool error = false;
    QNetworkRequest request;
    if(O1Requestor::instance().isLoggin())
    {
        QList<O1RequestParameter> reqParams = QList<O1RequestParameter>();
        reqParams << O1RequestParameter("per_page", PERPAGE);
        reqParams << O1RequestParameter("page", "1");
        //Возможна еще сортировка
        QByteArray data = O1Requestor::instance().createQueryParams(reqParams);

       // if (m_Folders.count()!=0 && ifolderALLIdToFilter<m_Folders.count()) {
     //   request =  QNetworkRequest(QUrl(m_Folders[ifolderALLIdToFilter].resourceUrl()+"/releases?" + data));
     //   } else
        request =  QNetworkRequest(QUrl(O1Requestor::instance().value("resource_url") + "/collection/folders/0/releases?" + data));

        do {

            if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
            {
                qDebug() << "ERROR get releases in Folder: ";
                error = true;

            } else {

                qDebug() << "Get releases in  OK";  // Думаю нужно определить folder - All по умолчанию. Затем, в зависимости от выбранной

                QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
                QJsonObject jsonObj = jsonResponse.object();
                QJsonObject pagination = jsonObj["pagination"].toObject();
                itemsInResult = pagination["items"].toInt();

                if (itemsInResult !=0)
                {
                    float incProgress = 0.01;

  //                  incProgress = 1/itemsInResult;
                    pagesInResult = pagination["pages"].toInt();
                    currentPage = pagination["page"].toInt();
                    QJsonObject resultUrls = pagination["urls"].toObject();
                    nextPageForSearh = resultUrls["next"].toString();
                    url = QUrl(nextPageForSearh);
                    QJsonArray result = jsonObj["releases"].toArray();
                    //Добавляем данные
                    emit beginInsertRows(QModelIndex(), rowCount(), rowCount()+result.size()-1);
                    for (QJsonArray::const_iterator iter = result.begin();iter!= result.end(); ++iter)
                    {
                        const QJsonObject o = (*iter).toObject();
                        //             qDebug() << "Release " << o;
                        m_instance = QString::number(o["instance_id"].toInt());
                        m_release = QString::number(o["id"].toInt());
                        m_folder = QString::number(o["folder_id"].toInt());
                        //Приходится повторять запрос в связи с тем, что в списке не возвращаются данные, введенные пользователем (notes)
                        QUrl u = QUrl(O1Requestor::instance().value("resource_url") + "/collection/folders/" + m_folder + "/releases/" + m_release + "/instances/" + m_instance);

                         request= QNetworkRequest(u);

                        if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
                        {
                            qDebug() << "ERROR Get Releases in Collection  ";
                            //                qDebug() << strReply;
                            addResult (o);   //Все равно получаем список без notes
                            fullResult.append(o);
                            progressValue_= progressValue_+incProgress;
                            qDebug() << "Progress - " << progressValue_;
                            emit progress();

                        } else {

                            qDebug() << "Get Releases in Collection OK";
                            //                 qDebug() << strReply;

                            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
                            QJsonObject jsonObj = jsonResponse.object();
                            //                qDebug() << "Instance" << jsonObj;
                            addResult (jsonObj);
                            fullResult.append(o);
                            progressValue_= progressValue_+incProgress;
                            qDebug() << "Progress - " << progressValue_;
                            emit progress();
                        }

                    }
                    emit endInsertRows();
                    request = QNetworkRequest(QUrl(url));
                }
            }
       }while ((currentPage<pagesInResult) && !error);

        if (!error)
        {
            f_CollectionResult = m_CollectionResult;
            //Пишем JSon в файл, если данные по сети были успешно считаны
            qDebug() << "Save Collection to file ";
            QFile collection(COLLECTION_FILENAME);
            if(!collection.open(QIODevice::WriteOnly))
            {
                qDebug() << "Couldn`t open  file to save";
            }
            else {
                QJsonDocument jsonToFile(fullResult);
                collection.write(jsonToFile.toJson());
                collection.close();
                 }
        } else {
     //       O1Requestor::instance().setIsLoggin(false);
            if (!readOffLineCollection()) {O1Requestor::instance().setIsOffline(false);  emit isOfflineChanged();}
        }
    } else
    {
        if(O1Requestor::instance().onlinked()) {
            if (!readOffLineCollection()) {O1Requestor::instance().setIsOffline(false);  emit isOfflineChanged();} }
    }
}


///*******************************************************************************************

bool CollectionModel::readOffLineCollection()
{
    QFile collection(COLLECTION_FILENAME);
    if (collection.exists())                              //Если есть файл с данными, читаем из него
    {

        if(!collection.open(QIODevice::ReadOnly))
        {
            qDebug() << "Couldn`t open collectionfile ";
            return false;
        } else
        {

            QByteArray saveData = collection.readAll();
            collection.close();
            QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
            QJsonArray result = loadDoc.array();
            qDebug() << "Collection in Json " <<result;
            if (result.size()>0)                   //Если в файле не ноль записей
            {
                emit beginInsertRows(QModelIndex(), rowCount(), rowCount()+result.size()-1);

                for (QJsonArray::const_iterator iter = result.begin();iter!= result.end(); ++iter)
                {
                    const QJsonObject o = (*iter).toObject();
                    //         qDebug() << "Release " << o;
                    addResult (o);
                }
                f_CollectionResult = m_CollectionResult;           //Копируем исходные данные в копию
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

void CollectionModel::addResult (const QJsonObject &o)
{

    int i;

    qDebug() << o;


    QJsonObject basicInformation = o["basic_information"].toObject();
    qDebug() <<  "basic_information " << basicInformation;


    BasicInfo i_basicInformation;

    QJsonArray labels = basicInformation["labels"].toArray();
    qDebug() << "Labels " << labels;

    QList<Companies> i_labels;

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



    m_CollectionResult << CollectionReleases(o["id"].toInt(),                            //наполнение исходной модели
            o["instance_id"].toInt(),
            o["folder_id"].toInt(),
            o["rating"].toInt(),
            i_basicInformation);


}

///*******************************************************************************************
/*
bool CollectionModel::getInstance (const int &index)
{
//    int i;
    QString m_instance;
    QString m_release;
    QString m_userName;
    QString m_folder;

    m_instance = QString::number(m_CollectionResult[index].instance());
    m_release = QString::number(m_CollectionResult[index].id());
    m_folder = QString::number(m_CollectionResult[index].folder_id());
    m_userName = O1Requestor::instance().value("username");

    QUrl u = QUrl("https://api.discogs.com/users/"+m_userName + "/collection/folders/" + m_folder + "/releases/" + m_release + "/instances/" + m_instance);


//    QUrl u = QUrl(m_CollectionResult[index].basicInformation().resourceURL());
    QNetworkRequest request(u);
    QString strReply;

    if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
    {
        qDebug() << "ERROR GetInstance:";
        qDebug() << strReply;
        return false;
    } else {

        qDebug() << "Get instance OK";
        qDebug() << strReply;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();
        qDebug() << "Instance" << jsonObj;



         return true;

    }


}
*/
///*******************************************************************************************
bool CollectionModel::canFetchMore(const QModelIndex &parent) const
{
    /*
    if (parent.isValid())
    {
        return false;
    }  else if (waitFirstSearch())
    {
        return false;
    } else return currentPage < pagesInResult ? true : false;
*/
    return false;

}
///*******************************************************************************************

void CollectionModel::fetchMore(const QModelIndex &parent)
{
    if (!parent.isValid())
    {

        //      getData(pagesAtNextSearch);

    }
}


///*********************************************************************************************************

int CollectionModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return f_CollectionResult.count();
}

QVariant CollectionModel::data(const QModelIndex & index, int role) const
{
   const int i = index.row();
   if (i < 0 || i >= f_CollectionResult.count())
       return QVariant();
   if(!index.isValid())
       return QVariant();
//    qDebug() << role << i;

     const CollectionReleases &oneCollectionResult = f_CollectionResult[i];
 //   const int j = f_CollectionResult[i].basicInformation().notes().count();  //узнаем сколько объектов Notes есть у релиза, добавленного в коллекцию пользователем
 //   qDebug() << j;

    //   enum CollectionModelRoles {Title= Qt::UserRole + 1,Year, Thumb, FormatShort, LabelShort, LabelName, Catno, ArtistName, Notes, Rating, Folder};

    switch(role)
    {
    case Title:
        return oneCollectionResult.basicInformation().title();
    case Year:
        return oneCollectionResult.basicInformation().year();
    case Thumb:
        return oneCollectionResult.basicInformation().thumb();
    case FormatShort:
        return qlistToString(oneCollectionResult.basicInformation().formats().description());
    case LabelShort:
        return labelNameToString(oneCollectionResult.basicInformation().labels());          // предусмотреть возврат списка и контроль индекса
    case Catno:
        return labelCatnoToString(oneCollectionResult.basicInformation().labels());
    case ArtistName:
        return oneCollectionResult.basicInformation().artists().name();
    case Rating:
        return oneCollectionResult.rating();
    case Folder:
        return nameOfFolder(oneCollectionResult.folder_id());
  /*
    case Field1:
        if (j < 1)
            return QVariant();
        return nameOfField(oneCollectionResult.basicInformation().notes()[0].field_id())+ " - " + oneCollectionResult.basicInformation().notes()[0].value();
    case Field2:
          if (j < 2)
              return QVariant();
        return nameOfField(oneCollectionResult.basicInformation().notes()[1].field_id())+" - " + oneCollectionResult.basicInformation().notes()[1].value();
      case Field3:
          if (j < 3)
              return QVariant();
        return nameOfField(oneCollectionResult.basicInformation().notes()[1].field_id())+" - " + oneCollectionResult.basicInformation().notes()[1].value();
*/

    }
    return  QVariant();
}

/// ***********************************************************************************************************************

QHash<int, QByteArray> CollectionModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[Title] = "Title";
    roles[Year] = "Year";
    roles[Thumb] = "Thumb";
    roles[FormatShort] = "FormatShort";
    roles[LabelShort] = "LabelShort";
    roles[Catno] = "Catno";
    roles[ArtistName] = "ArtistName";
    roles[Rating] = "Rating";
    roles[Folder] = "Folder";
    roles[Field1] = "Field1";
    roles[Field2] = "Field2";
    roles[Field3] = "Field3";


    return roles;
}
/// ***********************************************************************************************************************
/*
QVariant CollectionModel::proxy()
{
    qDebug() << "proxy ";
//    QSortFilterProxyModel * oneModel = &m_sortFilterProxyModel;
    qDebug() << QVariant::fromValue(&m_sortFilterProxyModel);
    return QVariant::fromValue(&m_sortFilterProxyModel);
}
*/
/// ***********************************************************************************************************************
QString CollectionModel::qlistToString(const QList<QString> & inpitList) const
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
QString CollectionModel::labelNameToString(const QList<Companies> &companies) const
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
QString CollectionModel::labelCatnoToString(const QList<Companies> &companies) const
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
QString CollectionModel::nameOfFolder(const int & id) const
{

    int j=0;
    QList<Folders>::const_iterator i;
    for (i=m_Folders.begin(); i!=m_Folders.end(); ++i)
    {
     if((*i).id()==id) {return (*i).name();}
     j++;
    }

    return QString();
}


QString CollectionModel::nameOfField(const int & id) const
{
    int j=0;
    QList<Fields>::const_iterator i;
    for (i=m_Fields.begin(); i!=m_Fields.end(); ++i)
    {
     if((*i).id()==id) {return (*i).name();}
     j++;
    }
 return QString();
}
