//
// Created by user on 6/3/24.
//

#include "MyForvardList.h"

void MyForvardList::append(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
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

MyForvardList::MyForvardList(const MyForvardList& other): head{nullptr}, tail{nullptr}, curSize{0} {
    for (Node* node = other.head; node; node = node->next) {
        append(node->data);
    }
}

MyForvardList& MyForvardList::operator=(const MyForvardList& other) {
    if (this != &other) {
        for (Node* node = other.head; node; node = node->next) {
            append(node->data);
        }
    }
    return *this;
}

// Move ctor
MyForvardList::MyForvardList(
    MyForvardList&& other) noexcept { // r-value reference
    head = other.head;
    other.head = nullptr;
    tail = other.tail;
    other.tail = nullptr;
    curSize = other.curSize;
    other.curSize = 0;
}

// Move assignment operator
MyForvardList& MyForvardList::operator=(MyForvardList&& other) noexcept {
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

MyForvardList::~MyForvardList() {
    Node* node_next = nullptr;
    for (Node* node = head; node; node = node_next) {
        node_next = node->next;
        delete node;
    }
};

void MyForvardList::push_back(int value) {
    append(value);
};

void MyForvardList::insert(std::size_t pos, int value) {

    std::size_t i = 0;
    Node* prevNode = nullptr;
    std::size_t prevSize = curSize;
    for (Node* node = head; node; node = node->next, i++) {
        if (i == pos) {
            Node* newNode = new Node;
            newNode->data = value;
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

void MyForvardList::erase(std::size_t pos) {

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

std::size_t MyForvardList::size() const {
    return curSize;
};

int& MyForvardList::operator[](std::size_t pos) const {

    std::size_t i = 0;
    for (Node* node = head; node; node = node->next, i++) {
        if (i == pos) {
            return node->data;
        }
    }

    throw "out of the range";
};

MyForvardList::iterator& MyForvardList::iterator::operator++() {
    if (!ptr)
        throw "empty iterator";
    ptr = ptr->next;
    return *this;
}

MyForvardList::iterator MyForvardList::begin() const {
    return {head};
}

MyForvardList::iterator MyForvardList::end() {
    return {nullptr};
}

bool MyForvardList::iterator::operator!=(const iterator& other) {
    return ptr != other.ptr;
}

int& MyForvardList::iterator::get() {
    return ptr->data;
}

int& MyForvardList::iterator::operator*() {
    return get();
}

std::ostream& operator<<(std::ostream& os, const MyForvardList& rhs) {
    for (auto iter = rhs.begin(); iter != rhs.end(); ++iter) {
        if (iter != rhs.begin())
            os << ' ';
        os << *iter;
    }
    return os;
}
