#ifndef SEARCHRESULT
#define SEARCHRESULT

#include <header/search/artist.h>
#include <header/search/label.h>
#include <header/search/master.h>
#include <header/search/release.h>



class SearchResult
{

public:


    SearchResult(const bool isDummy,               //Конструтор без данных
                 const QString &type,
                 const bool isLoading,
                 const bool isArtist,
                 const bool isRelease,
                 const bool isMaster,
                 const bool isLabel,
                 const QString &title,
                 const QString &thumb,
                 const QString &resourceUrl,
                 const QString &labelshort,
                 const QString &format,
                 const QString &country,
                 const QString &year,
                 const QString &catno,
                 const QString &genre,
                 const QString &style);
/*
    SearchResult(const bool isDummy,               //Конструтор c двумя дополнительными полями
                 const QString &type,
                 const bool isLoading,
                 const bool isArtist,
                 const bool isRelease,
                 const bool isMaster,
                 const bool isLabel,
                 const QString &title,
                 const QString &thumb,
                 const QString &resourceUrl,
                 const QString &labelshort,
                 const QString &format,
                 const QString &country,
                 const QString &year,
                 const QString &catno,
                 const QString &genre,
                 const QString &style);
 //                const bool &isInWl,
 //                const bool &isInCl

*/
   SearchResult(const bool isDummy);

   SearchResult();                         //Конструтор пустой
   ~SearchResult();



                         bool isDummy() const;
                         QString type() const;
                         bool isLoading() const;
                         bool isArtist() const;
                         bool isRelease() const;
                         bool isMaster() const;
                         bool isLabel() const;
                         Artist artist() const;
                         Release release() const;
                         Master master() const;
                         Label label() const;
                         QString title() const;
                         QString thumb() const;
                         QString resourceUrl() const;
                         QString labelshort() const;
                         QString format() const;
                         QString country() const;
                         QString year() const;
                         QString catno() const;
                         QString genre() const;
                         QString style() const;
                         bool isInWl() const;
                         bool isInCl() const;
                         QString resurceUrlInCollection() const;


                         void setRelease(const Release &r);
                         void setMaster(const Master &r);
                         void setLabel (const Label &r);
                         void setArtist(const Artist &r);
                         void setIsLoading (const bool &a);
                         void setResourceUrlInCollection(const QString &a);
                         void setIsInWl(const bool &a);
                         void setIsInCl(const bool &a);
                         int instanceInCollection() const;
                         void setInstanceInCollection(const int &a);


    private:
                         bool a_isDummy;
                         QString a_type;
                         bool a_isLoading;
                         bool a_isArtist;
                         bool a_isRelease;
                         bool a_isMaster;
                         bool a_isLabel;
                         Artist a_artist;
                         Release a_release;
                         Master a_master;
                         Label a_label;
                         QString a_title;
                         QString a_thumb;
                         QString a_resourceUrl;
                         QString a_labelshort;
                         QString a_format;
                         QString a_country;
                         QString a_year;
                         QString a_catno;
                         QString a_genre;
                         QString a_style;
                         bool a_isInWl;
                         bool a_isInCl;
                         QString a_resourceUrlInCollection;
                         int a_instanceInCollection;

    };


#endif // SEARCHRESULT

