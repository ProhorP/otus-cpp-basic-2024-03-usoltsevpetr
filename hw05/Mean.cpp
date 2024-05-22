//
// Created by user on 5/22/24.
//

#include "Mean.h"

void Mean::update(double next) {
    cnt++;
    sum += next;
}

double Mean::eval() const {
    if (cnt == 0)
        return 0;
    else
        return sum / cnt;
}

const char* Mean::name() const {
    return "mean";
}