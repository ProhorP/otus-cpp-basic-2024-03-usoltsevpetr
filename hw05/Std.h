//
// Created by user on 5/22/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_STD_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_STD_H

#include "IStatistics.h"
#include "Mean.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class Std : public IStatistics {
  public:
    Std() = default;

    void update(double next) override;

    double eval() const override;

    const char* name() const override;

  private:
    std::vector<double> line;
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_STD_H
