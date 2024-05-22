//
// Created by user on 5/22/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_PCT_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_PCT_H

#include "IStatistics.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include "IStatistics.h"


class Pct : public IStatistics {
  public:
    Pct(double percent);

    void update(double next) override ;

    double eval() const override ;

    const char* name() const override ;

  private:
    std::vector<double> line;
    double percent;
    std::string namePrint;
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_PCT_H
