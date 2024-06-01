//
// Created by user on 6/1/24.
//

#include "MyVector.h"

MyVector::MyVector(const MyVector& other) {
    data = new int[other.capacity];
    for (std::size_t i = 0; i < other.curSize; ++i) {
        data[i] = other.data[i];
    }
    curSize = other.curSize;
    capacity = other.capacity;
}

MyVector& MyVector::operator=(const MyVector& other) {
    if (this != &other) {
        data = new int[other.capacity];
        for (std::size_t i = 0; i < other.curSize; ++i) {
            data[i] = other.data[i];
        }
        curSize = other.curSize;
        capacity = other.capacity;
    }
    return *this;
}

// Move ctor
MyVector::MyVector(MyVector&& other)  noexcept { // r-value reference
    data = other.data;
    other.data = nullptr;
    curSize = other.curSize;
    other.curSize = 0;
    capacity = other.capacity;
    other.capacity = 0;
}

// Move assignment operator
MyVector& MyVector::operator=(MyVector&& other)  noexcept {
    if (this != &other) {
        data = other.data;
        other.data = nullptr;
        curSize = other.curSize;
        other.curSize = 0;
        capacity = other.capacity;
        other.capacity = 0;
    }
    return *this;
}

MyVector::~MyVector() {
    delete[] data;
};

void MyVector::realloc() {

    if (curSize > capacity) {
        std::size_t oldCapacity = capacity;
        capacity = curSize * 2;
        if (data) {
            int* tmpData = new int[capacity];
            for (std::size_t i = 0; i < oldCapacity; ++i)
                tmpData[i] = data[i];
            delete[] data;
            data = tmpData;
            tmpData = nullptr;
        } else {
            data = new int[capacity];
        }
    }
}

void MyVector::push_back(int next) {

    curSize++;

    realloc();

    data[curSize - 1] = next;
};

bool MyVector::check_position(std::size_t pos) const {
    if (pos >= curSize) {
        std::cout << "invalid position: " << pos << std::endl;
        return false;
    }
    return true;
}

void MyVector::insert(std::size_t pos, int next) {

    if (!check_position(pos))
        return;

    curSize++;

    realloc();

    if (curSize > 1) {
        for (std::size_t i = curSize - 2; i >= pos; --i) {
            data[i + 1] = data[i];
        }
    }

    data[pos] = next;
};

void MyVector::erase(std::size_t pos) {

    if (!check_position(pos))
        return;

    if (curSize) {
        curSize--;
        for (std::size_t i = pos; i < curSize; ++i) {
            data[i] = data[i + 1];
        }
    }
};

std::size_t MyVector::size() const {
    return curSize;
};

int& MyVector::operator[](std::size_t pos) const {

    if (!check_position(pos))
        throw "fail";

    return data[pos];
};

MyVector::iterator& MyVector::iterator::operator++() {
    ptr++;
    return *this;
}

MyVector::iterator MyVector::begin() const {
    return {data};
}

MyVector::iterator MyVector::end() const {
    return {data + curSize};
}

bool MyVector::iterator::operator!=(const iterator& other) {
    return ptr != other.ptr;
}

int& MyVector::iterator::get() {
    return *ptr;
}

int& MyVector::iterator::operator*() {
    return get();
}

std::ostream& operator<<(std::ostream& os, const MyVector& rhs) {
    for (auto iter = rhs.begin(); iter != rhs.end(); ++iter) {
        if (iter != rhs.begin())
            os << ' ';
        os << *iter;
    }
    return os;
}
