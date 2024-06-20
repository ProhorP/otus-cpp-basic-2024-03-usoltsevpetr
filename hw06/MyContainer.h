//
// Created by user on 6/1/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYCONTAINER_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYCONTAINER_H
#include <cstddef>

template <typename T>
class MyContainer {
  public:
    virtual ~MyContainer() = default;

    virtual void push_back(T value) = 0;
    virtual void insert(std::size_t pos, T value) = 0;
    virtual void erase(std::size_t pos) = 0;
    virtual void clean() = 0;
    virtual std::size_t size() const = 0;
    virtual T& operator[](std::size_t pos) const = 0;
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MYCONTAINER_H
