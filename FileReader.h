#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include "DSString.h"

using namespace std;

/**
 * Comments and implementation contained in FileReader.cpp
 */
class FileReader {
public:
    explicit FileReader(const char* path, int readSize = 256);
    ~FileReader();
    char* readLine();
    bool ready();
private:
    ifstream* buffer = nullptr;
    char* bufferLine = nullptr;
    int readSize = 0;
};

#endif //FILEREADER_H
