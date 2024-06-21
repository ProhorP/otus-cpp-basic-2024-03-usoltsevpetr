//
// Created by user on 6/1/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYVECTOR_HPP
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYVECTOR_HPP
#include "MyContainer.h"
#include <iostream>

template <typename T>
class MyVector: public MyContainer<T> {

  public:
    MyVector() : data{nullptr}, curSize{0}, capacity{0}{};

    MyVector(const MyVector& other) {
        data = new T[other.capacity];
        for (std::size_t i = 0; i < other.curSize; ++i) {
            data[i] = other.data[i];
        }
        curSize = other.curSize;
        capacity = other.capacity;
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            clean();
            data = new T[other.capacity];
            for (std::size_t i = 0; i < other.curSize; ++i) {
                data[i] = other.data[i];
            }
            curSize = other.curSize;
            capacity = other.capacity;
        }
        return *this;
    }

    // Move assignment operator
    MyVector& operator=(MyVector&& other)  noexcept {
        if (this != &other) {
            clean();
            data = other.data;
            other.data = nullptr;
            curSize = other.curSize;
            other.curSize = 0;
            capacity = other.capacity;
            other.capacity = 0;
        }
        return *this;
    }

    // Move ctor
    MyVector(MyVector&& other)  noexcept { // r-value reference
        data = other.data;
        other.data = nullptr;
        curSize = other.curSize;
        other.curSize = 0;
        capacity = other.capacity;
        other.capacity = 0;
    }

    void clean() override {
        delete[] data;
        curSize = 0;
        capacity = 0;
    };

    ~MyVector() override{
        clean();
    };

    void push_back(T value) override{

        curSize++;

        realloc();

        data[curSize - 1] = value;
    };

    void insert(std::size_t pos, T value) override{

        check_position(pos);

        curSize++;

        realloc();

        if (curSize > 1) {
            for (std::size_t i = curSize - 2; i >= pos; --i) {
                data[i + 1] = data[i];
                if (i == 0)
                    break;
            }
        }

        data[pos] = value;
    };

    void erase(std::size_t pos) override {

        check_position(pos);

        if (curSize) {
            curSize--;
            for (std::size_t i = pos; i < curSize; ++i) {
                data[i] = data[i + 1];
            }
        }
    };

    std::size_t size() const override{
        return curSize;
    };

    T& operator[](std::size_t pos) const override{

        check_position(pos);

        return data[pos];
    };
//    std::ostream& operator<<(std::ostream& os) const;

    struct iterator{
      public:
        explicit iterator(T *ptr) : ptr{ptr}{};

        iterator& operator++() {
            ptr++;
            return *this;
        }

        bool operator!=(const iterator& other) {
            return ptr != other.ptr;
        }

        T& operator*() {
            return get();
        }

        T& get() {
            return *ptr;
        }

      private:
        T *ptr;
    };

    iterator begin() const {
        return iterator(data);
    }

    iterator end() const {
        return iterator(data + curSize);
    }

  private:

    void realloc() {

        if (curSize > capacity) {
            std::size_t oldCapacity = capacity;
            capacity = curSize * 2;
            if (data) {
                T* tmpData = new T[capacity];
                for (std::size_t i = 0; i < oldCapacity; ++i)
                    tmpData[i] = data[i];
                delete[] data;
                data = tmpData;
                tmpData = nullptr;
            } else {
                data = new T[capacity];
            }
        }
    }

    void check_position(std::size_t pos) const {
        if (pos >= curSize)
            throw "out of the range";
    }
    T *data;
    std::size_t curSize;
    std::size_t capacity;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& rhs) {
    for (auto iter = rhs.begin(); iter != rhs.end(); ++iter) {
        if (iter != rhs.begin())
            os << ' ';
        os << *iter;
    }
    return os;
}

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYVECTOR_HPP
