//
// Created by user on 6/1/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYVECTOR_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYVECTOR_H
#include "MyContainer.h"
#include <iostream>

class MyVector: public MyContainer {

  public:
    MyVector() : data{nullptr}, curSize{0}, capacity{0}{};
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept ;
    MyVector(MyVector&& other) noexcept ;
    ~MyVector() override;

    void push_back(int value) override;
    void insert(std::size_t pos, int value) override;
    void erase(std::size_t pos) override;
    std::size_t size() const override;
    int& operator[](std::size_t pos) const override;
//    std::ostream& operator<<(std::ostream& os) const;

    struct iterator{
      public:
        iterator(int *ptr) : ptr{ptr}{};
        iterator& operator++();
        bool operator!=(const iterator& other);
        int& operator*();
        int& get();

      private:
        int *ptr;
    };

    iterator begin() const;
    iterator end() const ;

  private:
    void realloc();
    bool check_position(std::size_t pos) const;
    int *data;
    std::size_t curSize;
    std::size_t capacity;
};

std::ostream& operator<<(std::ostream& os, const MyVector &rhs) ;

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYVECTOR_H
