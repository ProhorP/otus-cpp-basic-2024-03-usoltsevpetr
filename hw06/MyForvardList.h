//
// Created by user on 6/3/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_H

#include "MyContainer.h"
#include <iostream>

class MyForvardList: public MyContainer {

  public:
    MyForvardList() : data{nullptr}, curSize{0}, capacity{0}{};
    MyForvardList(const MyForvardList& other);
    MyForvardList& operator=(const MyForvardList& other);
    MyForvardList& operator=(MyForvardList&& other) noexcept ;
    MyForvardList(MyForvardList&& other) noexcept ;
    ~MyForvardList() override;

    void push_back(int next) override;
    void insert(std::size_t pos, int next) override;
    void erase(std::size_t pos) override;
    std::size_t size() const override;
    int& operator[](std::size_t pos) const override;
    std::ostream& operator<<(std::ostream& os) const;

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

std::ostream& operator<<(std::ostream& os, const MyForvardList &rhs) ;

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_H
