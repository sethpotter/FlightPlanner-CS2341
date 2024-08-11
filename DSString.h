#ifndef DSSTRING_H
#define DSSTRING_H

#include "DSVector.h"
#include <iostream>
#include <ostream>

using namespace std;

class DSString {
public:
    explicit DSString(char* text);
    DSString(const char* text = nullptr);
    DSString(const DSString& obj);
    ~DSString();

    DSString& operator = (const DSString& obj);
    DSString operator + (DSString& obj);
    DSString& operator += (DSString& obj);
    bool operator == (const DSString& obj) const;
    bool operator != (const DSString& obj) const;
    bool operator < (const DSString& obj) const;
    int operator > (const DSString& obj) const;

    DSString& operator = (const char* text);
    DSString operator + (const char* text);
    DSString& operator += (const char* text);
    bool operator == (const char* text) const;
    bool operator != (const char* text) const;
    char operator [] (int index) const;

    friend ostream& operator << (ostream& os, DSString& obj);
    friend istream& operator >> (istream& is, DSString& obj);

    char* cstring() const;
    bool empty();

    DSString substring(int start, int end);
    DSVector<DSString> split(const char* delimiter);
    DSVector<DSString> split(const char* delimiter, int count);
    int firstIndexOf(const char* str);
    int lastIndexOf(const char* str);
    int indexOf(const char* str, int start=0, int skip=0);
    bool startsWith(const char* str);
    bool endsWith(const char* str);
    int size() const;
    DSString toLowercase();
    DSString toUppercase();
private:
    char* text = nullptr;
    int length = 0;
};

#endif // DSSTRING_H
