#include <header/search/companies.h>

Companies::Companies(const QString &catno, const QString &entity_type, const QString &entity_type_name,
                     const int &id, const QString &name, const QString &resourceUrl):
    i_catno(catno), i_entity_type(entity_type), i_entity_type_name(entity_type_name),
    i_id(id), i_name(name),i_resourceUrl(resourceUrl)
{

}

///************************************************************************************************************
Companies::Companies()
{

}

///************************************************************************************************************
Companies::~Companies()
{

}

///************************************************************************************************************
QString Companies::catno() const
{
    return i_catno;
}

///************************************************************************************************************
QString Companies::entity_type() const
{
    return i_entity_type;
}

///************************************************************************************************************
QString Companies::entity_type_name() const
{
    return i_entity_type_name;
}

///************************************************************************************************************
int Companies::id() const
{
    return i_id;
}

///************************************************************************************************************
QString Companies::name() const
{
    return i_name;
}

///************************************************************************************************************
QString Companies::resourceUrl() const
{
    return i_resourceUrl;
}

