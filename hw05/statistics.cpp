#include "IStatistics.h"
#include "Max.h"
#include "Mean.h"
#include "Min.h"
#include "Pct.h"
#include "Std.h"
#include <iostream>
#include <vector>

int main() {

    IStatistics* statistics[] = {new Min{}, new Max{}, new Mean{}, new Std{}, new Pct(90.0), new Pct(95.0)};

    double val = 0;
    while (std::cin >> val) {
        for (auto& statistic : statistics) {
            statistic->update(val);
        }
    }

    // Handle invalid input data
    if (!std::cin.eof() && !std::cin.good()) {
        std::cerr << "Invalid input data\n";
        return 1;
    }

    // Print results if any
    for (auto& statistic : statistics) {
        std::cout << statistic->name() << " = " << statistic->eval()
                  << std::endl;
    }

    // Clear memory - delete all objects created by new
    for (auto& statistic : statistics) {
        delete statistic;
    }

    return 0;
}