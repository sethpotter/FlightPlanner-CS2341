#ifndef DSLIST_H
#define DSLIST_H

#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

/**
 * DSList class. DSList is a doubly linked list. It has a head and tail with bidirectional nodes.
 * @tparam T value
 */
template <class T>
class DSList {
public:
    /// DSList class default constructor.
    DSList() = default;

    /// DSList class destructor.
    ~DSList() {
        clear();
    }

    /// DSList class copy constructor.
    DSList(const DSList<T> &obj) {
        *this = obj;
    }

    /// DSList class self-assignment copy constructor.
    DSList<T>& operator = (const DSList<T> &rhs) {
        if(head != nullptr) { // Nested Delete.
            clear();
        }
        if(&rhs != nullptr && rhs.head != nullptr) { // Nested Copy.
            head = new Node<T>(*rhs.head);
            tail = head;
            Node<T>* currLhs = head;
            Node<T>* currRhs = rhs.head;
            while(currRhs->next != nullptr) {
                currRhs = currRhs->next;
                Node<T>* newNode = new Node<T>(*currRhs);
                currLhs->next = newNode;
                newNode->previous = currLhs;
                currLhs = currLhs->next;
                tail = currLhs;
            }
        }
        return *this;
    }

    /// DSList class equals operator.
    bool operator == (const DSList<T> &rhs) const {
        if(size() != rhs.size())
            return false;

        bool equal = true;
        Node<T>* curr = head;
        Node<T>* rhsCurr = rhs.head;
        while(curr != nullptr) {
            if(rhsCurr == nullptr || *curr->getData() != *rhsCurr->getData())
                equal = false;
            curr = curr->next;
            rhsCurr = rhsCurr->next;
        }
        return equal;
    }

    /**
     * List subscript operator. Acts like a normal array subscript operator.
     * @param index
     * @return Templated value of list.
     */
    T& operator [] (int index) {
        if(head == nullptr) {
            throw out_of_range("DSList exception was thrown: out of range while trying to use subscript operator. List is empty.");
        } else {
            int s = size() - 1;
            if(index < 0 || index > s)
                throw out_of_range("DSList exception was thrown: out of range while trying to use subscript operator.");
            Node<T>* curr = head;
            for(int i = 0; i < index; i++)
                curr = curr->next;
            return *curr->getData();
        }
    }

    /**
     * Pushes a value into the list.
     * @param val
     */
    void push(const T& val) {
        if(head == nullptr) {
            head = new Node<T>(val);
            tail = head;
        } else {
            Node<T>* temp = new Node<T>(val);
            temp->previous = tail;
            tail->next = temp;
            tail = tail->next;
        }
    }

    /**
     * Returns the head node.
     */
    Node<T>* first() {
        return head;
    }

    /**
     * Returns the tail node.
     */
     Node<T>* last() {
         return tail;
     }

    /**
     * Removes the last value from the list and returns it. If the list is empty, an exception is thrown.
     * @return a copy of the tail value.
     */
    T pop() {
        if(head == nullptr)
            throw out_of_range("DSList exception was thrown: out of range while trying to pop. List is empty.");
        if(head->next == nullptr) {
            T val = *(head->getData());
            delete head;
            head = nullptr;
            tail = nullptr;
            return val;
        } else {
            T val = *(tail->getData());
            Node<T>* temp = tail;
            tail = tail->previous;
            tail->next = nullptr;
            delete temp;
            return val;
        }
    }

    /**
     * Removes the value from this list
     * @param data
     * @return Boolean whether removing was successful.
     */
    bool remove(const T& data) {
        Node<T>* temp = find(data);
        if(temp != nullptr) {
            Node<T>* prev = temp->previous;
            Node<T>* next = temp->next;

            if(prev == nullptr) { // If temp is head.
                if(next == nullptr) { // Only the head is in list?
                    head = nullptr;
                    tail = nullptr;
                    delete temp;
                } else {
                    head = next;
                    head->previous = nullptr;
                    delete temp;
                }
            } else if(next == nullptr) { // If temp is tail.
                tail = prev;
                tail->next = nullptr;
                delete temp;
            } else {
                next->previous = prev;
                prev->next = next;
                delete temp;
            }
            return true;
        }
        return false;
    }

    /**
     * Used for debugging purposes. Prints the list
     */
    void print() {
        cout << "[";
        Node<T>* curr = head;
        if(curr != nullptr) {
            while (curr->next != nullptr) {
                cout << *(curr->getData()) << ", ";
                curr = curr->next;
            }
            cout << *curr->getData();
        }
        cout << "]" << endl;
    }

    /**
     * Searches the list for val and returns the node found.
     * @param val
     * @return The node if found. Otherwise nullptr.
     */
    Node<T>* find(const T& val) {
        Node<T>* curr = head;
        while(curr != nullptr) {
            if(*curr->getData() == val)
                return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    /**
     * Searches the list for val and returns bool is found.
     * @param val
     * @return Bool if this list has the value.
     */
    bool has(const T& val) {
        return (find(val) != nullptr);
    }

    /**
     * Clears the list. This function deletes all nodes present in the list.
     */
    void clear() {
        Node<T>* curr = nullptr;
        while(tail != nullptr) {
            curr = tail->previous;
            delete tail;
            tail = curr;
        }
        head = nullptr;
        tail = nullptr;
    }

    /**
     * @return A boolean representing if the list is empty.
     */
    bool empty() {
        return (head == nullptr);
    }

    /**
     * @return The number of elements in the list.
     */
    int size() const {
        int size = 0;
        Node<T>* curr = head;
        while(curr != nullptr) {
            size++;
            curr = curr->next;
        }
        return size;
    }
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
};

#endif //DSLIST_H
