#include "header/collection/Fieldsmodel.h"
#include <header/system/qmltyperegistrator.h>
#include <header/system/o2globals.h>

namespace {
QmlTypeRegistrator registrator(qmlRegisterType<FieldsModel>("FieldsModel",1,0,"FieldsModel"));
}

///*******************************************************************************************************
///
FieldsModel::FieldsModel(QObject *parent)  //Конструктор модели, считаваем fields пользователя
{
    qDebug() << "FieldsModel constructor ";
    timeOut = 10000;
    if (O1Requestor::instance().isLoggin())
    {
     getFields();
    }

}

///*******************************************************************************************
void FieldsModel::clear()
{
    //Тут удаляем ранее считанные данные о релизах в коллекции
    emit beginResetModel();
    m_Fields.clear();
    emit endResetModel();

    emit fieldsChanged();

}


///*******************************************************************************************
void FieldsModel::refresh()
{
  //    m_isNotEmpty = false;

    //Если уже список был сформирован, то пока предлагаю его обнулить и считать заново
       if (m_Fields.count()!=0)
        {
           emit beginResetModel();
           clear();
           emit endResetModel();
        }
       getFields();
       emit fieldsChanged();

}


///*******************************************************************************************************
void FieldsModel::getFields()
{
    bool error = false;
    QString strReply;
    QJsonArray fullResult;

    if(O1Requestor::instance().isLoggin())
    {

        QNetworkRequest request(QUrl(O1Requestor::instance().value("collection_fields_url")));

        if (!O1Requestor::instance().getWithWait(request,strReply, timeOut))
        {
            qDebug() << "ERROR get Fields:";
            error = true;

        } else {

            qDebug() << "Get Fields collection OK";
            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
            QJsonObject jsonObj = jsonResponse.object();
            QJsonArray fields = jsonObj["fields"].toArray();
            qDebug() << "Fields in Json " <<jsonObj;

            emit beginInsertRows(QModelIndex(), rowCount(), rowCount()+fields.size()-1);
            for (QJsonArray::const_iterator iter = fields.begin(); iter!= fields.end(); ++iter)
            {

                const QJsonObject o = (*iter).toObject();
                QJsonArray options = o["options"].toArray();
                QStringList i_options;
                for (int i=0; i<options.size();i++)
                {
                    i_options << options.at(i).toString();
                }
                bool i_isDropdown;
                if (o["type"].toString()=="dropdown")
                    i_isDropdown = true;
                else i_isDropdown = false;

                m_Fields << Fields(o["name"].toString(),
                        i_options,
                        o["id"].toInt(),
                        o["position"].toInt(),
                        o["type"].toString(),
                        o["public"].toBool(),
                        o["lines"].toInt(),
                        i_isDropdown);
                fullResult.append(o);
            }
            emit endInsertRows();
        }
        if (!error)
        {
            //Пишем JSon в файл, если данные по сети были успешно считаны
            qDebug() << "Save Fields to file ";
            QFile fieldslist(FIELDS_FILENAME);
            if(!fieldslist.open(QIODevice::WriteOnly))
            {
                qDebug() << "Couldn`t open  file to save";
            }
            else {
                QJsonDocument jsonToFile(fullResult);
                fieldslist.write(jsonToFile.toJson());
                fieldslist.close();
            }
        } else {
      //      O1Requestor::instance().setIsLoggin(false);
            if(!readOffLineFields()) {O1Requestor::instance().setIsOffline(false); emit isOfflineChanged();}
         }
    } else
       {
        if(O1Requestor::instance().onlinked()) {
        if (!readOffLineFields()) {O1Requestor::instance().setIsOffline(false); emit isOfflineChanged();} }
       }
}


bool FieldsModel::readOffLineFields()
{
    QFile wntlist(FIELDS_FILENAME);
    if (wntlist.exists())                              //Если есть файл с данными, читаем из него
    {

        if(!wntlist.open(QIODevice::ReadOnly))
        {
            qDebug() << "Couldn`t open fieldsfile ";
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
                    QJsonArray options = o["options"].toArray();
                    QStringList i_options;
                    for (int i=0; i<options.size();i++)
                    {
                        i_options << options.at(i).toString();
                    }
                    bool i_isDropdown;
                    if (o["type"].toString()=="dropdown")
                        i_isDropdown = true;
                    else i_isDropdown = false;


                    m_Fields << Fields(o["name"].toString(),
                            i_options,
                            o["id"].toInt(),
                            o["position"].toInt(),
                            o["type"].toString(),
                            o["public"].toBool(),
                            o["lines"].toInt(),
                            i_isDropdown);
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
bool FieldsModel::canFetchMore(const QModelIndex &parent) const
{
     return false;                    //новых записей по умолчанию нет
}
///*******************************************************************************************

void FieldsModel::fetchMore(const QModelIndex &parent)
{
                                      //Ничего не читаем
}
///*********************************************************************************************

int FieldsModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_Fields.count();
}
///******************************************************************************************************************
bool FieldsModel::isOffline()
{
    return O1Requestor::instance().isOffline();
}

///*********************************************************************************************
QVariant FieldsModel::data(const QModelIndex & index, int role) const
{
    const int i = index.row();
    if (i < 0 || i >= m_Fields.count())
        return QVariant();

    const Fields oneFields = m_Fields[i];

    switch(role)
    {
    case Name:
        return oneFields.name();
    case id:
        return oneFields.id();
    case Position:
        return oneFields.position();
    case Type:
        return oneFields.type();
    case Public:
        return oneFields.public_();
    case Lines:
        return oneFields.lines();
    case CountOptions:
        return oneFields.options().count();
    case Options:
        return oneFields.options();
    case isDropdown:
        return oneFields.isDropdown();
    case Model:
         return QVariant::fromValue(oneFields.model_());
    }
    return  QVariant();
}

/// ***********************************************************************************************************************

QHash<int, QByteArray> FieldsModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[Name] = "Name";
    roles[id] = "id";
    roles[Position] = "Position";
    roles[Type] = "Type";
    roles[Public] = "Public";
    roles[Lines] = "Lines";
    roles[CountOptions] = "CountOptions";
    roles[Options] = "Options";
    roles[isDropdown]= "isDropdown";
    roles[Model]="Model";

    return roles;
}

