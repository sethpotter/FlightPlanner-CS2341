#include <cstring>
#include <iostream>
#include <ostream>
#include "DSString.h"

using namespace std;

DSString::DSString(char* text) : text(text) {
    length = strlen(text);
}

DSString::DSString(const char* text) {
    *this = text;
}

DSString::DSString(const DSString& obj) {
    *this = obj.text;
}

DSString::~DSString() {
    if(text != nullptr)
        delete[] text;
}

DSString& DSString::operator = (const DSString& rhs) {
    return (*this = rhs.text);
}

DSString DSString::operator + (DSString& rhs) {
    return *this + rhs.text;
}

DSString& DSString::operator += (DSString& rhs) {
    return *this += rhs.text;
}

bool DSString::operator == (const DSString& obj) const {
    if(text == nullptr && obj.text == nullptr) {
        return true;
    } else if(text == nullptr || obj.text == nullptr) {
        return false;
    }
    return (strcmp(text, obj.text) == 0);
}

bool DSString::operator != (const DSString& obj) const {
    return !(*this == obj.text);
}

bool DSString::operator < (const DSString& obj) const {
    if(text == nullptr || obj.text == nullptr) {
        throw invalid_argument("DSString class: Cannot compare with null string.");
    }
    int val = strcmp(text, obj.text);
    return (val < 0);
}

int DSString::operator > (const DSString& obj) const {
    if(text == nullptr || obj.text == nullptr) {
        throw invalid_argument("DSString class: Cannot compare with null string.");
    }
    int val = strcmp(text, obj.text);
    return (val > 0);
}

DSString& DSString::operator = (const char* rhs) {
    if(text != nullptr)
        delete[] text;
    text = nullptr;
    if(rhs != nullptr) {
        length = strlen(rhs);
        text = new char[length + 1];
        strcpy(text, rhs);
        text[length] = '\0';
    }
    return *this;
}

bool DSString::operator != (const char* rhs) const {
    return !(*this == rhs);
}

DSString DSString::operator + (const char* rhs) {
    DSString clone(*this);
    clone += rhs;
    return clone;
}

DSString& DSString::operator += (const char* rhs) {
    if(rhs == nullptr) {
        return *this;
    } else if(text == nullptr) {
        return (*this = rhs);
    } else {
        length += strlen(rhs);
        char* tempPtr = text;
        text = new char[length + 1];
        strcpy(text, tempPtr);
        strcat(text, rhs);
        delete[] tempPtr;
        return *this;
    }
}

bool DSString::operator == (const char* rhs) const {
    if(text == nullptr && rhs == nullptr) {
        return true;
    } else if(text == nullptr || rhs == nullptr) {
        return false;
    }
    return (strcmp(text, rhs) == 0);
}

char DSString::operator [] (int index) const {
    if(text == nullptr) {
        throw invalid_argument("DSString class: Cannot get subscript of null string.");
    } else {
        if(index < 0 || index > length)
            throw out_of_range("DSString class: Subscript index is out of bounds");
        return text[index];
    }
}

ostream& operator << (ostream& os, DSString& obj) {
    if(obj.text != nullptr)
        os << obj.text;
    return os;
}

istream& operator >> (istream &is, DSString &obj) {
    is >> obj.text;
    return is;
}

char* DSString::cstring() const {
    return text;
}

DSString DSString::substring(int start, int end) {
    if(text == nullptr) {
        throw invalid_argument("DSString class: cannot substring a null string.");
    } else if(start < 0 || end < 0 || start > length || end > length) {
        throw out_of_range("DSString class: substring out of bounds.");
    } else if(start > end) {
        throw invalid_argument("DSString class: substring start is larger than end.");
    } else if(length == 0 || start == end) {
        return DSString("");
    } else {
        int ssl = end - start;
        char* temp = new char[ssl + 1];
        for (int i = start; i < start + ssl; i++) {
            temp[i - start] = text[i];
        }
        temp[ssl] = '\0';
        return DSString(temp);
    }
}

bool DSString::empty() {
    return (text == nullptr || length == 0);
}

DSVector<DSString> DSString::split(const char* delimiter) {
    return split(delimiter, length);
}

DSVector<DSString> DSString::split(const char* delimiter, int count) {
    DSVector<DSString> list;
    int delimSize = 0;
    if (text == nullptr) {
        throw runtime_error("DSString class: cannot split null string.");
    } else if (delimiter == nullptr) {
        throw runtime_error("DSString class: cannot split using null delimiter.");
    } else {
        delimSize = strlen(delimiter);
        if (length == 0 || delimSize == 0 || count <= 0) {
            return list;
        } else if (delimSize >= length) {
            throw runtime_error("DSString class: cannot split with a delimiter >= than text length.");
        }
    }
    char* copy = new char[length + 1];
    strcpy(copy, text);
    copy[length] = '\0';

    int splitCount = 0;
    DSString clone(copy);
    int di = clone.firstIndexOf(delimiter);
    while(di >= 0 && splitCount < count) {
        list.push_back(clone.substring(0, di));
        int temp = di + delimSize;
        clone = clone.substring(temp, clone.size());
        di = clone.firstIndexOf(delimiter);
        splitCount++;
    }
    if(!clone.empty())
        list.push_back(clone);
    return list;
}

int DSString::firstIndexOf(const char* str) {
    return indexOf(str, 0, 0);
}

int DSString::lastIndexOf(const char* str) {
    int i = -1;
    int lastIndex = -1;
    while(i + 1 < length - 1) {
        i = indexOf(str, i + 1);
        if(i == -1) {
            return lastIndex;
        }
        lastIndex = i;
    }
    return lastIndex;
}

int DSString::indexOf(const char* str, int start, int skip) {
    int strLength;
    if(text == nullptr) {
        throw runtime_error("DSString class: cannot index null string.");
    } else if(str == nullptr) {
        throw runtime_error("DSString class: cannot index using a null string.");
    } else {
        strLength = strlen(str);
        if (length == 0 || strlen(str) > length) {
            return -1;
        } else if (start < 0 || start >= length) {
            throw out_of_range("DSString class: out of bounds start index.");
        } else if (skip < 0 || skip > length) {
            throw out_of_range("DSString class: out of bounds skip index.");
        }
    }
    int skipCount = 0;
    int i = start;
    while(i < length) {
        int si = 0;
        while(i + si < length && text[i + si] == str[si] && si < strLength) {
            si++;
        }
        if(si >= strLength) {
            if(skipCount >= skip)
                return i;
            else
                skipCount++;
        }
        i++;
    }
    return -1;
}

bool DSString::startsWith(const char* str) {
    int inputLen = strlen(str);
    if(text == nullptr)
        throw runtime_error("DSString class: cannot use startsWith on null string.");
    if(inputLen > length)
        throw out_of_range("DSString class: input string is too large.");
    for(int i = 0; i < inputLen; i++) {
        if(text[i] != str[i]) {
            return false;
        }
    }
    return true;
}

bool DSString::endsWith(const char* str) {
    int inputLen = strlen(str);
    if(text == nullptr)
        throw runtime_error("DSString class: cannot use endsWith on null string.");
    if(inputLen > length)
        throw out_of_range("DSString class: input string is too large.");
    int diff = length - inputLen;
    for(int i = 0; i < inputLen; i++) {
        if(text[i + diff] != str[i]) {
            return false;
        }
    }
    return true;
}

int DSString::size() const {
    return length;
}

DSString DSString::toLowercase() {
    if(text == nullptr) {
        throw runtime_error("DSString class: cannot index null string.");
    } else {
        if(length == 0) {
            return *this;
        } else {
            for(int i = 0; i < length; i++) {
                text[i] = tolower(text[i]);
            }
            return *this;
        }
    }
}

DSString DSString::toUppercase() {
    if(text == nullptr) {
        throw runtime_error("DSString class: cannot index null string.");
    } else {
        if(length == 0) {
            return *this;
        } else {
            for(int i = 0; i < length; i++) {
                text[i] = toupper(text[i]);
            }
            return *this;
        }
    }
}
