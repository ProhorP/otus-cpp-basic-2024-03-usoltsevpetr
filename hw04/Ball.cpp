#include "Ball.hpp"
#include <cmath>

/**
 * Задает скорость объекта
 * @param attrVelocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& attrVelocity) {
    // TODO: место для доработки
    velocity = Velocity(attrVelocity.vector());
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // TODO: место для доработки
    return velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    // TODO: место для доработки
    painter.draw(center, radius, color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& otherCenter) {
    // TODO: место для доработки
    center = Point(otherCenter.x, otherCenter.y);

}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // TODO: место для доработки
    return radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: место для доработки
    return M_PI * std::pow(radius, 3) * 4 / 3;
}

Ball::Ball(const Ball &other) {
    radius = other.radius;
    color = other.color;
    setVelocity(other.getVelocity());
    setCenter(other.getCenter());
}

Ball& Ball::operator=(const Ball &other){
    if (this != &other){
        radius = other.radius;
        color = other.color;
        setVelocity(other.getVelocity());
        setCenter(other.getCenter());
    }
    return *this;
}
