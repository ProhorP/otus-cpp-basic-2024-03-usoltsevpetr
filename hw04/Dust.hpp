//
// Created by user on 5/12/24.
//

#ifndef OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_DUST_HPP
#define OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_DUST_HPP

#include "Painter.hpp"
#include "Velocity.hpp"

class Dust {

  public:
    inline Dust() {
        setTimer(2000);
    };
    Dust(const Dust& other);
    Dust& operator=(const Dust& other);
    inline ~Dust() = default;

    void setVelocity(const Velocity& attrVelocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    void setTimer(size_t otherTimer);
    size_t getTimer() const;

  private:
    Velocity velocity;
    Point center;
    size_t timer;
};

#endif // OTUS_CPP_BASIC_2024_03_USOLTSEVPETR_DUST_HPP
