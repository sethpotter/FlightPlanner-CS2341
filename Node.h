#ifndef NODE_H
#define NODE_H

/**
 * Node class. Contains a next and previous pointer, along with a data pointer.
 * Usable in doubly or singly linked list.
 * @tparam T value
 */
template <class T>
class Node {
public:
    Node<T>* next = nullptr;
    Node<T>* previous = nullptr;

    /// Node class constructor.
    explicit Node(const T& data) {
        this->data = new T(data);
    }

    /// Node class move constructor.
    explicit Node(T* data) : data(data) {}

    /// Node class copy constructor.
    Node(const Node<T>& obj) {
        *this = obj;
    }

    /// Node class self-assignment copy constructor.
    Node<T>& operator = (const Node<T> &rhs) {
        if(data != nullptr)
            delete data;
        next = nullptr;
        previous = nullptr;
        if(&rhs != nullptr) {
            data = new T(*rhs.data);
            next = rhs.next;
            previous = rhs.previous;
        }
        return *this;
    }

    /// Node class equals operator.
    bool operator == (const Node<T> &rhs) {
        return *data == *rhs.data;
    }

    /// Node class destructor.
    ~Node() {
        if(data != nullptr)
            delete data;
    }

    T* getData() {
        return data;
    }
private:
    T* data = nullptr;
};

#endif //NODE_H
