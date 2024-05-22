//
// Created by user on 5/22/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_ISTATISTICS_H
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_ISTATISTICS_H

class IStatistics {
  public:
    virtual ~IStatistics() {}

    virtual void update(double next) = 0;
    virtual double eval() const = 0;
    virtual const char* name() const = 0;
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_ISTATISTICS_H
