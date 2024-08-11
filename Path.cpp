#include "Path.h"

/**
 * Path class. Contains the data needed for a path.
 * @param path Path String
 * @param cost Cost for Travel
 * @param time Time for Travel
 */
Path::Path(const DSString& path, int cost, int time) {
    this->path = path;
    this->cost = cost;
    this->time = time;
}

/// Path class destructor.
Path::~Path() {
    // Destructor does not seem needed in this case..
    // DSString will self delete when outside scope.
}

/// Path class copy constructor.
Path::Path(const Path &rhs) {
    *this = rhs;
}

/// Path class self-assignment copy constructor.
Path& Path::operator = (const Path &rhs) {
    path = rhs.path;
    cost = rhs.cost;
    time = rhs.time;
}

/// Path class less than operator.
bool Path::operator == (const Path &rhs) const {
    return (path == rhs.path && time == rhs.time && cost == rhs.cost);
}

/// Path class bitwise operator.
ostream& operator << (ostream &os, Path &obj) {
    if(obj.path != nullptr)
        os << obj.path << " " << obj.cost << " " << obj.time;
    return os;
}

/**
 * @return Get the path
 */
DSString Path::getPath() const {
    return path;
}

/**
 * @return Cost of travel.
 */
int Path::getCost() const {
    return cost;
}

/**
 * @return Time for travel.
 */
int Path::getTime() const {
    return time;
}