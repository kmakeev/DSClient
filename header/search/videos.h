#ifndef VIDEOS
#define VIDEOS

#include <QVariant>

class Videos
{
public:
    Videos(const QString &description, const int &duration,const bool &embed, const QString &title, const QString &uri);

    Videos();
    ~Videos();


    QString description() const;
    int duration() const;
    bool embed() const;
    QString title() const;
    QString uri() const;

private:
    QString i_description;
    int i_duration;
    bool i_embed;
    QString i_title;
    QString i_uri;

};


#endif // VIDEOS

