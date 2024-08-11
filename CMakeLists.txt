cmake_minimum_required(VERSION 3.14)
project(20f-flt-pln)
set (EXE_NAME flight_planner)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++ -pedantic -std=c++0x") # Make Compiler stop rebuilding catch.

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "")
set (input02 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02)
    configure_file(${file} ${file} COPYONLY)
endforeach()

file(COPY data DESTINATION ./)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-O3") # Remove debug symbols
add_executable(${EXE_NAME} main.cpp test.cpp DSString.cpp City.cpp FlightPlanner.cpp FileReader.cpp Path.cpp)

