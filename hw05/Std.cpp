//
// Created by user on 5/22/24.
//

#include "Std.h"

void Std::update(double next) {
    line.push_back(next);
}

double Std::eval() const {

    Mean mean;
    for (auto& entry : line)
        mean.update(entry);
    double mean_value = mean.eval();

    Mean mean_square;
    for (auto& entry : line)
        mean_square.update(pow(entry - mean_value, 2));

    return sqrt(mean_square.eval());
}

const char* Std::name() const {
    return "std";
}