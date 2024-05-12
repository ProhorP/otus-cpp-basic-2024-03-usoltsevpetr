//
// Created by user on 5/12/24.
//

#include "Dust.hpp"

Dust::Dust(const Dust& other) {
    setVelocity(other.getVelocity());
    setCenter(other.getCenter());
    setTimer(other.getTimer());
}

Dust& Dust::operator=(const Dust& other) {
    if (this != &other) {
        setVelocity(other.getVelocity());
        setCenter(other.getCenter());
        setTimer(other.getTimer());
    }
    return *this;
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Dust::setCenter(const Point& otherCenter) {
    // TODO: место для доработки
    center = Point(otherCenter.x, otherCenter.y);
}

/**
 * @return центр объекта
 */
Point Dust::getCenter() const {
    // TODO: место для доработки
    return center;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Dust абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Dust::draw(Painter& painter) const {
    // TODO: место для доработки
    if (timer)
        painter.draw(center, 10.0, Color(1, 0, 0));
}

/**
 * Задает скорость объекта
 * @param attrVelocity новое значение скорости
 */
void Dust::setVelocity(const Velocity& attrVelocity) {
    // TODO: место для доработки
    velocity = Velocity(attrVelocity.vector());
}

/**
 * @return скорость объекта
 */
Velocity Dust::getVelocity() const {
    // TODO: место для доработки
    return velocity;
}

void Dust::setTimer(size_t otherTimer) {
    timer = otherTimer;
}

size_t Dust::getTimer() const {
    return timer;
}
