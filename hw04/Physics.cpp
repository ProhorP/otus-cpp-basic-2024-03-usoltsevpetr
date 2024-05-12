#include "Physics.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if (!a->getIsCollidable())
            continue;
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (!b->getIsCollidable())
                continue;

            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2);
                addDusts(*a);
                addDusts(*b);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
        ball.moveDusts(timePerTick);
    }
}

void Physics::addDusts(Ball& ball) const{

    //добавляем эффекты для каждого шара, а не в мир, чтобы не менять интерфейс

    for (int i = 0 ; i < 4; ++i) {
        Dust dust;
        dust.setCenter(ball.getCenter());

        switch (i) {
        case 0:
            dust.setVelocity(Velocity(500, 1000));
            break;;
        case 1:
            dust.setVelocity(Velocity(-500, 1000));
            break;;
        case 2:
            dust.setVelocity(Velocity(500, -1000));
            break;;
        case 3:
            dust.setVelocity(Velocity(-500, -1000));
            break;
        default:
            break;
        }

        ball.addDust(dust);
    }

}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}
