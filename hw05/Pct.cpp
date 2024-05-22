//
// Created by user on 5/22/24.
//

#include "Pct.h"

Pct::Pct(double percent) : percent{percent} {
    namePrint += "pct" + std::to_string(static_cast<int>(percent));
};

void Pct::update(double next) {
    line.push_back(next);
}

double Pct::eval() const {

    std::vector<double> sort_line(line);
    std::sort(sort_line.begin(), sort_line.end());
    double step = 100.0 / static_cast<double>(sort_line.size());
    double cur_percent = 0;
    size_t index = 0;
    while (index != sort_line.size()) {
        cur_percent += step;
        if (cur_percent > percent)
            break;
        ++index;
    }

    return sort_line[index];
}

const char* Pct::name() const {
    return namePrint.c_str();
}