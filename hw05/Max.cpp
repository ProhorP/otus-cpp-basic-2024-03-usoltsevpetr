//
// Created by user on 5/22/24.
//

#include "Max.h"

void Max::update(double next) {
    if (first || next > m_max) {
        m_max = next;
    }
    first = false;
}

double Max::eval() const {
    return m_max;
}

const char* Max::name() const {
    return "max";
}
