//
// Created by user on 6/3/24.
//

#include "MyList.h"

void MyList::append(int value) {
    Node* tmpNew = new Node;
    tmpNew->data = value;
    tmpNew->next = nullptr;
    tmpNew->prev = nullptr;
    if (!head)
        head = tmpNew;
    if (tail) {
        tail->next = tmpNew;
        tail = tmpNew;
    } else {
        tail = tmpNew;
    }
    curSize++;
}

MyList::MyList(const MyList& other): head{nullptr}, tail{nullptr}, curSize{0} {
    for (Node* tmp = other.head; tmp; tmp = tmp->next) {
        append(tmp->data);
    }
}

MyList& MyList::operator=(const MyList& other) {
    if (this != &other) {
        for (Node* tmp = other.head; tmp; tmp = tmp->next) {
            append(tmp->data);
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
    Node* tmp_next = nullptr;
    for (Node* tmp = head; tmp; tmp = tmp_next) {
        tmp_next = tmp->next;
        delete tmp;
    }
};

void MyList::push_back(int value) {
    append(value);
};

void MyList::insert(std::size_t pos, int value) {

    std::size_t i = 0;
    Node* prev_tmp = nullptr;
    std::size_t prevSize = curSize;
    for (Node* tmp = head; tmp; tmp = tmp->next, i++) {
        if (i == pos) {
            Node* tmpNew = new Node;
            tmpNew->data = value;
            if (prev_tmp) {
                tmpNew->next = prev_tmp->next;
                prev_tmp->next = tmpNew;
            } else {
                tmpNew->next = head;
                head = tmpNew;
            }
            curSize++;
            break;
        }
        prev_tmp = tmp;
    }
    if (curSize == prevSize)
        append(value);
};

void MyList::erase(std::size_t pos) {

    std::size_t i = 0;
    Node* prev_tmp = nullptr;
    for (Node* tmp = head; tmp; tmp = tmp->next, i++) {
        if (i == pos) {
            if (prev_tmp) {
                prev_tmp->next = tmp->next;
            } else {
                head = tmp->next;
            }
            if (tail == tmp)
                tail = prev_tmp;
            curSize--;
            delete tmp;
            break;
        }
        prev_tmp = tmp;
    }
};

std::size_t MyList::size() const {
    return curSize;
};

int& MyList::operator[](std::size_t pos) const {

    std::size_t i = 0;
    for (Node* tmp = head; tmp; tmp = tmp->next, i++) {
        if (i == pos) {
            return tmp->data;
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

MyList::iterator MyList::begin() const {
    return {head};
}

MyList::iterator MyList::end() const {
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
