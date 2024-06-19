//
// Created by user on 6/3/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYLIST_HPP
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYLIST_HPP

#include "MyContainer.h"
#include <iostream>

template <typename T> class MyList : public MyContainer {

  public:
    MyList() : head{nullptr}, tail{nullptr}, curSize{0} {};

    MyList(const MyList& other) : head{nullptr}, tail{nullptr}, curSize{0} {
        for (Node* node = other.head; node; node = node->next) {
            append(node->data);
        }
    }

    MyList& operator=(const MyList& other) {
        if (this != &other) {
            for (Node* node = other.head; node; node = node->next) {
                append(node->data);
            }
        }
        return *this;
    }

    // Move ctor
    MyList(MyList&& other) noexcept { // r-value reference
        head = other.head;
        other.head = nullptr;
        tail = other.tail;
        other.tail = nullptr;
        curSize = other.curSize;
        other.curSize = 0;
    }

    // Move assignment operator
    MyList& operator=(MyList&& other) noexcept {
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

    ~MyList() override {
        Node* node_next = nullptr;
        for (Node* node = head; node; node = node_next) {
            node_next = node->next;
            delete node;
        }
    };

    void push_back(T value) override {
        append(value);
    };

    void insert(std::size_t pos, T value) override {

        std::size_t i = 0;
        Node* prevNode = nullptr;
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

    std::size_t size() const override {
        return curSize;
    };

    T& operator[](std::size_t pos) const override {

        std::size_t i = 0;
        for (Node* node = head; node; node = node->next, i++) {
            if (i == pos) {
                return node->data;
            }
        }

        throw "out of the range";
    };

    struct Node {
        Node* next;
        Node* prev;
        T data;
    };

    struct iterator {
      public:
        iterator(Node* ptr) : ptr{ptr} {};
        iterator& operator++() {
            if (!ptr)
                throw "empty iterator";
            ptr = ptr->next;
            return *this;
        }
        iterator& operator--() {
            if (!ptr)
                throw "empty iterator";
            ptr = ptr->prev;
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
        Node* ptr;
    };

    iterator begin() const {
        return {head};
    }

    iterator end() const {
        return {nullptr};
    }

  private:
    void append(T value) {
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
    Node* head;
    Node* tail;
    std::size_t curSize;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyList<T>& rhs) {
    for (auto iter = rhs.begin(); iter != rhs.end(); ++iter) {
        if (iter != rhs.begin())
            os << ' ';
        os << *iter;
    }
    return os;
}
#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYLIST_HPP
