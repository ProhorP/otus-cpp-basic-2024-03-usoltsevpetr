//
// Created by user on 6/20/24.
//

#include "Widget.h"
Widget::Widget(const Widget& other) {
    ptr = other.ptr;
}

Widget& Widget::operator=(const Widget& other) {
    if (this != &other) {
        ptr = other.ptr;
    }
    return *this;
}

Widget::~Widget() {
    if (ptr)
        (*ptr)++;
}
