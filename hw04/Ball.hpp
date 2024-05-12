#pragma once
#include "Dust.hpp"
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include <vector>

class Ball {
  public:
    inline Ball(double radius, const Color& color, bool isCollidable)
        : radius(radius), color(color), isCollidable(isCollidable){};
    Ball(const Ball& other);
    Ball& operator=(const Ball& other);
    inline ~Ball() = default;

    void setVelocity(const Velocity& attrVelocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void drawDusts(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getIsCollidable() const;
    void addDust(Dust &dust);
    void moveDusts(double timePerTick);

  private:
    Velocity velocity;
    double radius;
    Point center;
    Color color;
    bool isCollidable;
    // Контейнер с эффектами
    std::vector<Dust> dusts;
};
