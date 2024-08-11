#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <ostream>
#include "DSString.h"

using namespace std;

/**
 * Comments and implementation contained in City.cpp
 */
class City {
public:
    City(const DSString& name, const DSString& airline, int cost, int time);
    ~City();
    City(const City& rhs);
    City& operator = (const City& rhs);
    bool operator == (const City& rhs) const;
    friend ostream& operator << (ostream& os, City& obj);
    DSString getName() const;
    DSString getAirline() const;
    int getCost() const;
    int getTime() const;
private:
    DSString name = nullptr;
    DSString airline = nullptr;
    int cost = 0;
    int time = 0;
};

#endif //CITY_H
