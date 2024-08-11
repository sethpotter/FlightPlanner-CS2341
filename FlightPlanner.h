#ifndef FLIGHTPLANNER_H
#define FLIGHTPLANNER_H

#include "DSAdjacencyList.h"
#include "DSString.h"
#include "City.h"
#include "FileReader.h"
#include "DSStack.h"
#include "Path.h"

using namespace std;

/**
 * FlightPlanner. Core of the program. Generates the AdjacencyList map and preforms iterative
 * backtracking on the map.
 *
 * Method documentation is in FlightPlanner.cpp
 */
class FlightPlanner {
public:
    static void GenerateMap(FileReader &file, DSAdjacencyList<DSString, City>& map);
    static void TracePaths(const char* outputFile, FileReader &file, DSAdjacencyList<DSString, City>& map);
    static void SortList(DSList<Path> &paths, char sortType);
private:
    static void WritePath(ofstream &out, int flightNum, DSString source, DSString dest, DSList<Path> &paths, char sortType);
};

#endif //FLIGHTPLANNER_H
