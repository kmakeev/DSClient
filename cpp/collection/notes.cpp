#include "header\collection\notes.h"

Notes::Notes(const int &field_id, const QString &value) : i_field_id(field_id), i_value(value)
{

}
///******************************************************************************************************************
Notes::Notes()
{

}
///******************************************************************************************************************
Notes::~Notes()
{

}
///******************************************************************************************************************
int Notes::field_id() const
{
    return i_field_id;
}
///******************************************************************************************************************
QString Notes::value() const
{
    return i_value;
}
