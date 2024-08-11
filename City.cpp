#include "City.h"

/**
 * City class. Contains the data needed for a city path.
 * @param name City Name
 * @param airline Airline Name
 * @param cost Cost for Travel
 * @param time Time for Travel
 */
City::City(const DSString& name, const DSString& airline, int cost, int time) {
    this->name = name;
    this->airline = airline;
    this->cost = cost;
    this->time = time;
}

/// City class destructor.
City::~City() {
    // Destructor does not seem needed in this case..
    // DSString will self delete when outside scope.
}

/// City class copy constructor.
City::City(const City &rhs) {
    *this = rhs;
}

/// City class self-assignment copy constructor.
City& City::operator = (const City &rhs) {
    name = rhs.name;
    airline = rhs.airline;
    cost = rhs.cost;
    time = rhs.time;
}

/// City class equals operator.
bool City::operator == (const City &rhs) const {
    return (name == rhs.name && airline == rhs.airline);
}

/// City class bitwise operator.
ostream& operator << (ostream &os, City &obj) {
    if(obj.name != nullptr && obj.airline != nullptr)
        os << obj.name << " " << obj.airline << " " << obj.cost << " " << obj.time;
    return os;
}

/**
 * @return The name for this city.
 */
DSString City::getName() const {
    return name;
}

/**
 * @return The name of the airline.
 */
DSString City::getAirline() const {
    return airline;
}

/**
 * @return Cost of travel.
 */
int City::getCost() const {
    return cost;
}

/**
 * @return Time for travel.
 */
int City::getTime() const {
    return time;
}