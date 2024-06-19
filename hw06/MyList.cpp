//
// Created by user on 6/3/24.
//

#include "MyList.h"

void MyList::append(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = tail;
    if (!head)
        head = newNode;
    if (tail) {
        tail->next = newNode;
        tail = newNode;
    } else {
        tail = newNode;
    }
    curSize++;
}

MyList::MyList(const MyList& other): head{nullptr}, tail{nullptr}, curSize{0} {
    for (Node* node = other.head; node; node = node->next) {
        append(node->data);
    }
}

MyList& MyList::operator=(const MyList& other) {
    if (this != &other) {
        for (Node* node = other.head; node; node = node->next) {
            append(node->data);
        }
    }
    return *this;
}

// Move ctor
MyList::MyList(
    MyList&& other) noexcept { // r-value reference
    head = other.head;
    other.head = nullptr;
    tail = other.tail;
    other.tail = nullptr;
    curSize = other.curSize;
    other.curSize = 0;
}

// Move assignment operator
MyList& MyList::operator=(MyList&& other) noexcept {
    if (this != &other) {
        head = other.head;
        other.head = nullptr;
        tail = other.tail;
        other.tail = nullptr;
        curSize = other.curSize;
        other.curSize = 0;
    }
    return *this;
}

MyList::~MyList() {
    Node* node_next = nullptr;
    for (Node* node = head; node; node = node_next) {
        node_next = node->next;
        delete node;
    }
};

void MyList::push_back(int value) {
    append(value);
};

void MyList::insert(std::size_t pos, int value) {

    std::size_t i = 0;
    Node* prevNode = nullptr;
    std::size_t prevSize = curSize;
    for (Node* node = head; node; node = node->next, i++) {
        if (i == pos) {
            Node* newNode = new Node;
            newNode->data = value;
            newNode->prev = prevNode;
            node->prev = newNode;
            if (prevNode) {
                newNode->next = prevNode->next;
                prevNode->next = newNode;
            } else {
                newNode->next = head;
                head = newNode;
            }
            curSize++;
            return;
        }
        prevNode = node;
    }

    throw "out of the range";
};

void MyList::erase(std::size_t pos) {

    std::size_t i = 0;
    Node* prevNode = nullptr;
    for (Node* node = head; node; node = node->next, i++) {
        if (i == pos) {
            if (prevNode) {
                prevNode->next = node->next;
            } else {
                head = node->next;
            }
            if (tail == node)
                tail = prevNode;
            curSize--;
            delete node;
            return;
        }
        prevNode = node;
    }
    throw "out of the range";
};

std::size_t MyList::size() const {
    return curSize;
};

int& MyList::operator[](std::size_t pos) const {

    std::size_t i = 0;
    for (Node* node = head; node; node = node->next, i++) {
        if (i == pos) {
            return node->data;
        }
    }

    throw "out of the range";
};

MyList::iterator& MyList::iterator::operator++() {
    if (!ptr)
        throw "empty iterator";
    ptr = ptr->next;
    return *this;
}

MyList::iterator& MyList::iterator::operator--() {
    if (!ptr)
        throw "empty iterator";
    ptr = ptr->prev;
    return *this;
}

MyList::iterator MyList::begin() const {
    return {head};
}

MyList::iterator MyList::end() {
    return {nullptr};
}

bool MyList::iterator::operator!=(const iterator& other) {
    return ptr != other.ptr;
}

int& MyList::iterator::get() {
    return ptr->data;
}

int& MyList::iterator::operator*() {
    return get();
}

std::ostream& operator<<(std::ostream& os, const MyList& rhs) {
    for (auto iter = rhs.begin(); iter != rhs.end(); ++iter) {
        if (iter != rhs.begin())
            os << ' ';
        os << *iter;
    }
    return os;
}
