//
// Created by user on 5/22/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MIN_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MIN_H

#include "IStatistics.h"

class Min : public IStatistics {
  public:
    Min() : m_min{0}, first{true} {}

    void update(double next) override;

    double eval() const override ;

    const char* name() const override ;

  private:
    double m_min;
    bool first;
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MIN_H
