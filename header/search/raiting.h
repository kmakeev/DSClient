#ifndef RAITING
#define RAITING

#include<QString>

class Raiting
{
public:
    Raiting(const int &average, const int count);
    Raiting();
    ~Raiting();

    int average() const;
    int count() const;

private:
    int i_average;
    int i_count;

};


#endif // RAITING

