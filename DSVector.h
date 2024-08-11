#ifndef DSVECTOR_H
#define DSVECTOR_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <class T>
class DSVector {
public:
    /// DSVector class default constructor.
    DSVector() {
        data = new T[dataSize];
    }

    /// DSVector class destructor.
    ~DSVector() {
        delete[] data;
    }

    /// DSVector class copy constructor.
    DSVector(const DSVector<T> &rhs) {
        *this = rhs;
    }

    /// DSVector class self-assignment copy constructor.
    DSVector<T>& operator = (const DSVector<T> &rhs) {
        if(&rhs != this) {
            delete[] data;
            pos = rhs.pos;
            dataSize = rhs.dataSize;
            T* temp = new T[dataSize];
            for(int i = 0; i < dataSize; i++) {
                temp[i] = rhs.data[i];
            }
            data = temp;
        }
        return *this;
    }

    /**
     * Subscript operator. Returns a value within the vector without preforming bound checking.
     * @param val index
     * @return value at the index.
     */
    T& operator [] (int val) {
        return data[val];
    }

    /**
     * Returns a value within the vector.
     * @param val index
     * @return value at the index.
     */
    T& at(int val) {
        if(val > -1 && val < pos)
            return data[val];
        throw out_of_range("DSVector exception was thrown: at() method out of bounds.");
    }

    /**
     * Pushes a value into the vector. Automatically resizes if vector is too small.
     */
    void push_back(const T& val) {
        if(pos < dataSize) {
            data[pos] = val;
            pos++;
        } else {
            T* temp = new T[dataSize * 2];
            for(int i = 0; i < dataSize; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            dataSize *= 2;
            data = temp;
            push_back(val);
        }
    }

    /**
     * Remove and return the last item within the vector.
     */
    T pop_back() {
        if(pos > 0) {
            pos--;
            return data[pos];
        }
        throw out_of_range("DSVector exception was thrown: Failed to pop_back(). Vector is empty.");
    }

    /**
     * Searches the vector for val and returns the index if found.
     * @param val
     * @return The index of the value if found. Otherwise -1
     */
    int find(const T& val) {
        for(int i = 0; i < pos; i++) {
            if(data[i] == val)
                return i;
        }
        return -1;
    }

    /**
     * Resets the position of the vector to 0 allowing previous positions to be overwritten.
     */
    void clear() {
        pos = 0;
    }

    /**
     * @return A boolean representing if the vector is empty.
     */
    bool empty() {
        return (pos == 0);
    }

    /**
     * @return The number of elements in the vector.
     */
    int size() {
        return pos;
    }

    /**
     * @return The number of elements the vector is able to hold.
     */
    int capacity() {
        return dataSize;
    }
private:
    T* data = nullptr;
    int dataSize = 4, pos = 0;
};

#endif //DSVECTOR_H
