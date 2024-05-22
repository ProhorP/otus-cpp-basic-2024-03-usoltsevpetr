//
// Created by user on 5/22/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MEAN_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MEAN_H

#include "IStatistics.h"

class Mean : public IStatistics {
  public:
    Mean() : cnt{0}, sum{0} {}

    void update(double next) override;

    double eval() const override;

    const char* name() const override;

  private:
    double cnt;
    double sum;
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MEAN_H
