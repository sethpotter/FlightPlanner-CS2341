#define CATCH_CONFIG_RUNNER
#include "includes/catch.hpp"

#include "FileReader.h"
#include "DSAdjacencyList.h"
#include "City.h"
#include "FlightPlanner.h"

int main(int argc, char** argv) {

    if(argc == 1)
    {
        Catch::Session().run();
    }
    else
    {
        cout << "File Paths: " << argv[1] << " " << argv[2] << " " << argv[3] << endl;

        /// Input Files.
        FileReader flightPlans(argv[1]);
        FileReader requestedFlights(argv[2]);

        /// Run Program
        DSAdjacencyList<DSString, City> map;
        FlightPlanner::GenerateMap(flightPlans, map);
        FlightPlanner::TracePaths(argv[3], requestedFlights, map);

        cout << "Complete. Output was sent to: " << argv[3] << endl;
    }

    return 0;
}

