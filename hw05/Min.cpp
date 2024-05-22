//
// Created by user on 5/22/24.
//

#include "Min.h"

void Min::update(double next) {
    if (first || next < m_min) {
        m_min = next;
    }
    first = false;
}

double Min::eval() const {
    return m_min;
}

const char* Min::name() const {
    return "min";
}
