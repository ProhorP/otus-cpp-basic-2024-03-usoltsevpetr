//
// Created by user on 6/20/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_WIDGET_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_WIDGET_H
#include <cstddef>

class Widget {

  public:
    explicit inline Widget(std::size_t *ptr) : ptr{ptr}{};
    Widget(const Widget& other);
    Widget& operator=(const Widget& other);
    ~Widget();

  private:
    std::size_t *ptr; //non free
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_WIDGET_H
