//
// Created by user on 5/22/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MAX_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MAX_H

#include "IStatistics.h"

class Max : public IStatistics {
  public:
    Max() : m_max{0}, first{true} {}

    void update(double next) override;

    double eval() const override;

    const char* name() const override;

  private:
    double m_max;
    bool first;
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_MAX_H
