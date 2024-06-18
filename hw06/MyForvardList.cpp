//
// Created by user on 6/3/24.
//

#include "MyForvardList.h"

bool MyForvardList::check_position(std::size_t pos) const {
    if (pos >= curSize) {
        std::cout << "invalid position: " << pos << std::endl;
        return false;
    }
    return true;
}

void MyForvardList::add(int value) {
    Node* tmpNew = new Node;
    tmpNew->data = value;
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

MyForvardList::MyForvardList(const MyForvardList& other) {
    for (Node* tmp = other.head; tmp; tmp = tmp->next) {
        add(tmp->data);
    }
}

MyForvardList& MyForvardList::operator=(const MyForvardList& other) {
    if (this != &other) {
        for (Node* tmp = other.head; tmp; tmp = tmp->next) {
            add(tmp->data);
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
    Node* tmp_next = nullptr;
    for (Node* tmp = head; tmp; tmp = tmp_next) {
        tmp_next = tmp->next;
        delete tmp;
    }
};

void MyForvardList::push_back(int next) {
    add(next);
};

void MyForvardList::insert(std::size_t pos, int next) {

    std::size_t i = 0;
    Node* prev_tmp = nullptr;
    std::size_t prevSize = curSize;
    for (Node* tmp = head; tmp; tmp = tmp->next, i++) {
        if (i == pos) {
            Node* tmpNew = new Node;
            tmpNew->data = next;
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
        add(next);
};

void MyForvardList::erase(std::size_t pos) {

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

std::size_t MyForvardList::size() const {
    return curSize;
};

int& MyForvardList::operator[](std::size_t pos) const {

    std::size_t i = 0;
    for (Node* tmp = head; tmp; tmp = tmp->next, i++) {
        if (i == pos) {
            return tmp->data;
        }
    }

    throw "out of the range";
};

MyForvardList::iterator& MyForvardList::iterator::operator++() {
    if (ptr)
        ptr = ptr->next;
    return *this;
}

MyForvardList::iterator MyForvardList::begin() const {
    return {head};
}

MyForvardList::iterator MyForvardList::end() const {
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
