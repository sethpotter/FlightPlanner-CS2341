#ifndef DSSTACK_H
#define DSSTACK_H

#include "DSList.h"

/**
 * DSStack class. Bare-bones wrapper class for the doubly-linked list class.
 */
template <class T>
class DSStack {
public:
    /// DSList class default constructor.
    DSStack() {
        list = new DSList<T>();
    }

    /// DSList class destructor.
    ~DSStack() {
        delete list;
    }

    /// DSList class copy constructor.
    DSStack(const DSStack<T> &obj) {
        *this = obj;
    }

    /// DSList class self-assignment copy constructor.
    DSStack<T>& operator = (const DSStack<T> &rhs) {
        list = rhs.list;
        return *this;
    }

    /**
     * Returns the last element pushed.
     * @return T data
     */
    T peek() {
        Node<T>* tail = list->last();
        return *tail->getData();
    }

    /**
     * Returns and removes the last element pushed onto the stack.
     * @return T data
     */
    T pop() {
        return list->pop();
    }

    /**
     * Pushes element onto the stack.
     * @param data
     */
    void push(const T& data) {
        list->push(data);
    }

    /**
     * Checks to see if data is contained on stack.
     * @param data
     * @return Boolean if this stack has data or not.
     */
    bool has(const T& data) {
        return list->has(data);
    }

    /**
     * @return A boolean whether the stack is empty or not.
     */
    bool isEmpty() {
        return list->empty();
    }

    /**
     * @return The list that represents this stack.
     */
    DSList<T>* getList() {
        return list;
    }

    /**
     * Prints the stack.
     */
    void print() {
        list->print();
    }
private:
    DSList<T>* list;
};

#endif //DSSTACK_H
