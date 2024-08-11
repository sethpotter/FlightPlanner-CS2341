#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <ostream>
#include "DSString.h"

using namespace std;

/**
 * Comments and implementation contained in Path.cpp
 */
class Path {
public:
    Path() = default;
    Path(const DSString& path, int cost, int time);
    ~Path();
    Path(const Path& rhs);
    Path& operator = (const Path& rhs);
    bool operator == (const Path& rhs) const;
    friend ostream& operator << (ostream& os, Path& obj);
    DSString getPath() const;
    int getCost() const;
    int getTime() const;
private:
    DSString path = nullptr;
    int cost = 0;
    int time = 0;
};

#endif //PATH_H
