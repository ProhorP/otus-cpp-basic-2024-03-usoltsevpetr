//
// Created by user on 6/3/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_HPP
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_HPP

#include "MyContainer.h"
#include <iostream>

template <typename T>
class MyForvardList: public MyContainer {

  public:
    MyForvardList() : head{nullptr}, tail{nullptr}, curSize{0}{};

    MyForvardList(const MyForvardList& other): head{nullptr}, tail{nullptr}, curSize{0} {
        for (Node* node = other.head; node; node = node->next) {
            append(node->data);
        }
    }

    MyForvardList& operator=(const MyForvardList& other) {
        if (this != &other) {
            for (Node* node = other.head; node; node = node->next) {
                append(node->data);
            }
        }
        return *this;
    }

    // Move assignment operator
    MyForvardList& operator=(MyForvardList&& other) noexcept {
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

    // Move ctor
    MyForvardList(
        MyForvardList&& other) noexcept { // r-value reference
        head = other.head;
        other.head = nullptr;
        tail = other.tail;
        other.tail = nullptr;
        curSize = other.curSize;
        other.curSize = 0;
    }

    ~MyForvardList() override{
        Node* node_next = nullptr;
        for (Node* node = head; node; node = node_next) {
            node_next = node->next;
            delete node;
        }
    };

    void push_back(T value) {
        append(value);
    };

    void insert(std::size_t pos, T value) override{

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

    void erase(std::size_t pos) override {

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

    std::size_t size() const override{
        return curSize;
    };

    T& operator[](std::size_t pos) const override{

        std::size_t i = 0;
        for (Node* node = head; node; node = node->next, i++) {
            if (i == pos) {
                return node->data;
            }
        }

        throw "out of the range";
    };

    struct Node{
        Node* next;
        T data;
    };

    struct iterator{
      public:
        explicit iterator(Node *ptr) : ptr{ptr}{};

        iterator& operator++() {
            if (!ptr)
                throw "empty iterator";
            ptr = ptr->next;
            return *this;
        }

        bool operator!=(const iterator& other) {
            return ptr != other.ptr;
        }

        T& operator*() {
            return get();
        }

        T& get() {
            return ptr->data;
        }

      private:
        Node *ptr;
    };

    iterator begin() const {
        return iterator(head);
    }

    iterator end() const {
        return iterator(nullptr);
    }

  private:
    void append(T value) {
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
    Node *head;
    Node *tail;
    std::size_t curSize;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyForvardList<T>& rhs) {
    for (auto iter = rhs.begin(); iter != rhs.end(); ++iter) {
        if (iter != rhs.begin())
            os << ' ';
        os << *iter;
    }
    return os;
}

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYFORVARDLIST_HPP
