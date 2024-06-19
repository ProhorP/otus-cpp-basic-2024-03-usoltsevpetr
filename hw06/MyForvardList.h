//
// Created by user on 6/3/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_H

#include "MyContainer.h"
#include <iostream>

class MyForvardList: public MyContainer {

  public:
    MyForvardList() : head{nullptr}, tail{nullptr}, curSize{0}{};
    MyForvardList(const MyForvardList& other) ;
    MyForvardList& operator=(const MyForvardList& other);
    MyForvardList& operator=(MyForvardList&& other) noexcept ;
    MyForvardList(MyForvardList&& other) noexcept ;
    ~MyForvardList() override;

    void push_back(int value) override;
    void insert(std::size_t pos, int value) override;
    void erase(std::size_t pos) override;
    std::size_t size() const override;
    int& operator[](std::size_t pos) const override;
//    std::ostream& operator<<(std::ostream& os) const;

    struct Node{
        Node* next;
        int data;
    };

    struct iterator{
      public:
        iterator(Node *ptr) : ptr{ptr}{};
        iterator& operator++();
        bool operator!=(const iterator& other);
        int& operator*();
        int& get();

      private:
        Node *ptr;
    };

    iterator begin() const;
    iterator end() const ;

  private:
    void append(int value);
    Node *head;
    Node *tail;
    std::size_t curSize;
};

std::ostream& operator<<(std::ostream& os, const MyForvardList &rhs) ;

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_H
