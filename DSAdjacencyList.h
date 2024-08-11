#ifndef DSADJACENCYLIST_H
#define DSADJACENCYLIST_H

#include "DSList.h"

/**
 * ListReference class. Simple holder for a list of values and a key.
 * @tparam K Key
 * @tparam V Value
 */
template <class K, class V>
class ListReference {
public:
    /// ListReference class constructor.
    explicit ListReference(const K& key) {
        this->key = new K(key);
        list = new DSList<V>();
    }

    /// ListReference class destructor.
    ~ListReference() {
        delete key;
        delete list;
    }

    /// ListReference class copy constructor.
    ListReference(const ListReference<K, V> &rhs) {
        *this = rhs;
    }

    /// ListReference class self-assignment copy constructor.
    ListReference<K, V>& operator = (const ListReference<K, V> &rhs) {
        if(key != nullptr)
            delete key;
        if(list != nullptr)
            delete list;
        key = new K(*rhs.key);
        list = new DSList<V>(*rhs.list);
        return *this;
    }

    /// ListReference class equals operator.
    bool operator == (const ListReference<K, V> &rhs) const {
        return (key == rhs.key && list == rhs.list);
    }

    /**
     * @return Key for this reference.
     */
    K* getKey() {
       return key;
    }

    /**
     * @return List of values for this reference.
     */
    DSList<V>* getList() {
        return list;
    }

    /**
     * Pushes a value into the list.
     * @param value
     */
    void add(const V& value) {
        list->push(value);
    }
private:
    K* key = nullptr;
    DSList<V>* list = nullptr;
};

/**
 * DSAdjacencyList class. DSAdjacencyList is similar to a map container. It has key and value pairs of the same data type.
 * This class uses multiple doubly-linked list in a pointer array to represent keys. Duplicate keys are not allowed.
 * Keys can share duplicate values, but a singular key cannot have duplicate values.
 * @tparam T value
 */
template <class K, class V>
class DSAdjacencyList {
public:
    /// DSAdjacencyList class constructor.
    DSAdjacencyList() {
        matrix = new DSList<ListReference<K, V>>();
    }

    /// DSAdjacencyList class destructor.
    ~DSAdjacencyList() {
        delete matrix;
    }

    /// DSAdjacencyList class copy constructor.
    DSAdjacencyList(const DSAdjacencyList<K, V> &rhs) {
        *this = rhs;
    }

    /// DSAdjacencyList class self-assignment copy constructor.
    DSAdjacencyList<K, V>& operator = (const DSAdjacencyList<K, V> &rhs) {
        matrix = rhs.matrix;
        return *this;
    }

    /**
     * AdjacencyList subscript operator.
     * @param index
     * @return Templated value of list.
     */
    K& operator [] (int index) {
        return matrix[index];
    }

    /**
     * Search the list of references for a matching key.
     * @param key
     * @return The reference containing the key.
     */
    ListReference<K, V>* find(const K& key) {
        Node<ListReference<K, V>>* curr = matrix->first();
        while(curr != nullptr) {
            ListReference<K, V>* ref = curr->getData();
            if(*(ref->getKey()) == key) {
                return ref;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    /**
     * Inserts a key and value pair. Creates a new key if the key does not exist.
     * Duplicate key-value pairs are not allowed.
     * @param key
     * @param value
     * @return Boolean whether the insert was successful.
     */
    bool insert(const K& key, const V& value) {
        // Search for a reference containing the key.
        ListReference<K, V>* ref = find(key);

        // If a reference containing key was found.
        if(ref != nullptr) {
            DSList<V>* list = ref->getList();
            if(!list->has(value)) {
                list->push(value);
            } else {
                // Duplicate value.
                return false;
            }
        } else {
            ListReference<K, V> tempRef(key);
            tempRef.add(value);
            matrix->push(tempRef);
        }
        return true;
    }

    /**
     * Removes a value belonging to a key.
     * @param key
     * @param value
     * @return Boolean whether removing was successful.
     */
    bool removeValue(const K& key, const V& value) {
        // Search for a reference containing the key.
        ListReference<K, V>* ref = find(key);

        // If a reference containing key was found.
        if(ref != nullptr) {
            DSList<V>* list = ref->getList();
            return list->remove(value);
        } else {
            return false;
        }
    }

    /**
     * Removes a key and all its values.
     * @param key
     * @param value
     * @return Boolean whether removing was successful.
     */
    bool removeKey(const K& key) {
        // Search for a reference containing the key.
        ListReference<K, V>* ref = find(key);

        if(ref != nullptr) {
            return matrix->remove(*ref);
        } else {
            return false;
        }
    }

    /**
     * Prints the adjacency list for debugging purposes.
     */
    void print() {
        cout << "-- Adjacency List --" << endl;
        Node<ListReference<K, V>>* curr = matrix->first();
        while(curr != nullptr) {
            ListReference<K, V>* ref = curr->getData();
            cout << "Key: " << *ref->getKey() << " Values: ";
            DSList<V>* data = ref->getList();
            data->print();
            curr = curr->next;
        }
        cout << "--------------------" << endl;
    }

private:
    DSList<ListReference<K, V>>* matrix;
};

#endif //DSADJACENCYLIST_H
