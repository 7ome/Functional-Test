#include "home.h"

class homeData : public QSharedData
{
public:

};

home::home() : data(new homeData)
{

}

home::home(const home &rhs) : data(rhs.data)
{

}

home &home::operator=(const home &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

home::~home()
{

}
