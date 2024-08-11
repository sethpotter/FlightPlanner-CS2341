#include "FlightPlanner.h"
#include "DSStack.h"
#include "Path.h"
#include <cstring>

/**
 * GenerateMap. Takes in an AdjacencyList and a File containing flight data in order to
 * generate a linked map for iterative backtracking.
 * @param file Flight data.
 * @param map Key pair based map.
 */
void FlightPlanner::GenerateMap(FileReader &file, DSAdjacencyList<DSString, City> &map) {
    char* line = file.readLine();

    while(line != nullptr) {
        DSString str = DSString(line);
        if(str.empty()) {
            line = file.readLine();
            continue;
        }

        DSVector<DSString> info = str.split("|");

        // CSV Data.
        DSString oneName = info.at(0);
        DSString twoName = info.at(1);
        int cost = atoi(info.at(2).cstring());
        int time = atoi(info.at(3).cstring());
        DSString airline = info.at(4);

        // Create Cities.
        City cityOne(oneName, airline, cost, time);
        City cityTwo(twoName, airline, cost, time);
        map.insert(oneName, cityTwo);
        map.insert(twoName, cityOne);

        line = file.readLine();
    }
}

/**
 * TracePaths takes in a FileReader and AdjacencyList map. This method generates paths using
 * iterative backtracking and then outputs to a file. The input file here- takes in flight requests
 * which are then used to create a flight path for the user.
 * @param file Flight requests.
 * @param map Key pair based map.
 */
void FlightPlanner::TracePaths(const char* outputFile, FileReader &file, DSAdjacencyList<DSString, City> &map) {

    // Create output file.
    ofstream out(outputFile);
    if(!out.is_open() || !out.good()) {
        cout << "Exception while trying to create output file." << endl;
        throw runtime_error(strerror(errno));
    }

    // Read in requested flights.
    char* line = file.readLine();
    int flightNum = 1;

    while(line != nullptr)
    {
        DSString str = DSString(line);
        if(str.empty()) {
            line = file.readLine();
            continue;
        }

        // Input file information. Source/Dest/Sorting Method
        DSVector<DSString> info = str.split("|");
        DSString source = info.at(0);
        DSString dest = info.at(1);
        DSString sort = info.at(2);

        DSStack<City> cityStack;
        DSStack<DSString> stack;
        DSList<Path> currentPaths;

        stack.push(source); // Push source onto stack.

        DSVector<int> iterators;
        iterators.push_back(0); // Prep iterators.
        int currItr = 0;

        bool broke = false;
        bool foundPath = false;

        while(!stack.isEmpty()) // Is stack empty?
        {
            ListReference<DSString, City>* ref = map.find(stack.peek()); // Get Connections for Stack.Top
            if(ref == nullptr) {
                stack.pop();
                continue;
            }

            DSList<City> connections = *ref->getList();

            broke = false; // Break label.

            if(stack.peek() == dest) // Top of stack equal to destination?
            {
                // Save path to paths list.
                DSList<City> temp = DSList<City>(*cityStack.getList());
                DSString path = source;
                DSString terminal = temp[0].getAirline();

                int cost = 0;
                int time = 0;

                for(int i = 0; i < temp.size(); i++)
                {
                    City c = temp[i];
                    if(i >= 1) { // Layover calculation.
                        time += 43;
                        cost += 19;
                    }
                    if(terminal != c.getAirline()) { // Terminal change calculation.
                        terminal = c.getAirline();
                        time += 22;
                    }
                    cost += c.getCost();
                    time += c.getTime();
                    path += " -> ";
                    path += c.getName().cstring();
                }

                currentPaths.push(Path(path, cost, time));
                foundPath = true;

                stack.pop();
                cityStack.pop();
                currItr--;
            }
            else
            {
                // Iterate through list.
                while(iterators[currItr] < connections.size())
                {
                    City city = connections[iterators[currItr]];
                    DSString cityName = city.getName();
                    if (stack.has(cityName)) { // Stack has city name?
                        iterators[currItr]++; // Inc iterator.
                        continue;
                    } else {
                        iterators[currItr]++; // Inc iterator.
                        stack.push(cityName); // Push connection to stack.
                        cityStack.push(city); // Push city to side-stack (Used in tracing the path for output)
                        iterators.push_back(0); // Create a new iterator.
                        currItr++; // Switch to the new iterator.
                        broke = true;
                        break;
                    }
                }

                // If we've reached the end of this list.
                if(!broke && iterators[currItr] >= connections.size())
                {
                    stack.pop();
                    if(!cityStack.isEmpty())
                        cityStack.pop();
                    currItr--;
                }
            }
        }

        // Sort and Write path to file.
        SortList(currentPaths, tolower(sort.cstring()[0]));
        WritePath(out, flightNum, source, dest, currentPaths, tolower(sort.cstring()[0]));
        if(!foundPath) {
            out << "Unable to find a path." << endl << endl;
        } else {
            out << endl;
        }

        // Next flight
        line = file.readLine();
        flightNum++;
    }
    out.close();
}

/**
 * Sorts a DSList of Paths.
 * @param paths List of paths
 * @param sortType Cost/Time
 */
void FlightPlanner::SortList(DSList<Path> &paths, char sortType) {
    if(paths.empty())
        return;

    Path unsorted[paths.size()];
    for(int i = 0; i < paths.size(); i++) {
        unsorted[i] = paths[i];
    }

    int size = paths.size();
    for(int i = 0; i < paths.size(); i++) {
        int li = i;
        for(int j = i + 1; j < paths.size(); j++) {
            if(sortType == 'c') {
                if(unsorted[j].getCost() < unsorted[li].getCost())
                    li = j;
            } else {
                if(unsorted[j].getTime() < unsorted[li].getTime())
                    li = j;
            }
        }
        Path temp = unsorted[li];
        unsorted[li] = unsorted[i];
        unsorted[i] = temp;

    }

    paths.clear();
    for(int i = 0; i < size; i++)
        paths.push(unsorted[i]);
}

/**
 * Outputs the flight data to a file.
 */
void FlightPlanner::WritePath(ofstream &out, int flightNum, DSString source, DSString dest, DSList<Path> &paths, char sortType) {
    out << "Flight " << flightNum << ": " << source << ", " << dest;
    if(sortType == 'c') {
        out << " (Cost)" << endl;
    } else {
        out << " (Time)" << endl;
    }
    int size = paths.size();
    if(size >= 3) {
        size = 3;
    }
    for(int i = 0; i < size; i++) {
        Path path = paths[i];
        out << "Path " << (i + 1) << ": " << path.getPath().cstring() << ". " << "Time: " << path.getTime() << " Cost: " << path.getCost() << ".00" << endl;
    }
}


