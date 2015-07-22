#include "header/collection/fields.h"

Fields::Fields(const QString &name, const QStringList &options, const int &id, const int &position, const QString &type, const bool &public_, const int &lines, const bool &isDropdown):
               f_name(name), f_options(options), f_id(id), f_position(position), f_type(type), f_public_(public_), f_lines(lines),f_isDropdown(isDropdown)
{
    f_model = new QStringListModel(f_options);

}
///******************************************************************************************************************
Fields::Fields()
{

}

///******************************************************************************************************************

QString Fields::name() const
{
   return f_name;
}
///******************************************************************************************************************
QStringList Fields::options() const
{
    return f_options;
}
///******************************************************************************************************************
int Fields::id() const
{
    return f_id;
}
///******************************************************************************************************************
int Fields::position() const
{
    return f_position;

}
///******************************************************************************************************************
QString Fields::type() const
{
    return f_type;
}
///******************************************************************************************************************
bool Fields::public_() const
{
    return f_public_;

}
///******************************************************************************************************************
int Fields::lines() const
{
return f_lines;
}
///******************************************************************************************************************

QStringListModel *Fields::model_() const
{
   return f_model;
}
///******************************************************************************************************************
///

bool Fields::isDropdown() const
{
return f_isDropdown;
}

///******************************************************************************************************************


Fields::~Fields()
{

}

