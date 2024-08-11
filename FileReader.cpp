#include "FileReader.h"
#include <cstring>

/**
 * FileReader class. Reads an input file line by line.
 * @param path Input file
 * @param readSize Buffer size
 */
FileReader::FileReader(const char* path, int readSize) {
    this->readSize = readSize;
    buffer = new ifstream(path);
    bufferLine = new char[readSize];

    if(!ready()) {
        cout << "FileReader class: error was thrown while trying to read file." << endl;
        throw runtime_error(strerror(errno));
    }
    buffer->getline(bufferLine, readSize);
}

/// FileReader class destructor.
FileReader::~FileReader() {
    buffer->close();

    delete buffer;
    delete[] bufferLine;
}

/**
 * @return Current line as const char *
 */
char* FileReader::readLine() {
    if(buffer->eof())
        return nullptr;

    buffer->getline(bufferLine, readSize);
    int length = strlen(bufferLine);
    char* temp = new char[length + 1];
    strcpy(temp, bufferLine);
    temp[length] = '\0';
    return temp;
}

/**
 * @return Boolean if FileReader is good to read.
 */
bool FileReader::ready() {
    return (buffer->is_open() && buffer->good());
}