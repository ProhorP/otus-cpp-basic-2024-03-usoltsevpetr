#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:

     inline Ball(const double Radius, const Color & BallColor) : Radius(Radius), BallColor(BallColor) {
          Mass = M_PI * std::pow(Radius, 3) * 4 / 3;
     }
     inline Ball(const Ball &other) {
          Radius = other.Radius;
          Mass = other.Mass;
          BallColor = other.BallColor;
          this->setVelocity(other.getVelocity());
          this->setCenter(other.getCenter());
     }
     inline Ball &operator=(const Ball &other){
          Radius = other.Radius;
          Mass = other.Mass;
          BallColor = other.BallColor;
          this->setVelocity(other.getVelocity());
          this->setCenter(other.getCenter());
          return *this;
     }
     inline ~Ball()= default;

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
  private:
    Velocity BallVelocity;
    double Radius;
    double Mass;
    Point Center;
    Color BallColor;
};
