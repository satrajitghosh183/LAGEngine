// engine/objects/Cannon2D.cpp
#include "engine/objects/Cannon2D.hpp"
#include <cmath>

namespace engine::objects {

    Cannon2D::Cannon2D(const sf::Vector2f& pos)
        : position(pos) {}

    void Cannon2D::rotate(float degrees) {
        angle += degrees;
        if (angle < -170.f) angle = -170.f; // Clamp rotation range
        if (angle > -10.f) angle = -10.f;
    }

    void Cannon2D::update(float) {
        // Cannon itself doesn't need physics updates
    }

    void Cannon2D::render(sf::RenderWindow& window) {
        sf::RectangleShape barrel(sf::Vector2f(50.f, 8.f));
        barrel.setOrigin(0.f, 4.f);
        barrel.setPosition(position);
        barrel.setRotation(angle);
        barrel.setFillColor(sf::Color::Red);
        window.draw(barrel);

        sf::CircleShape base(15.f);
        base.setOrigin(15.f, 15.f);
        base.setPosition(position);
        base.setFillColor(sf::Color::Blue);
        window.draw(base);
    }

    sf::Vector2f Cannon2D::getFiringVelocity() const {
        float rad = angle * 3.14159265f / 180.f;
        return { std::cos(rad) * power, std::sin(rad) * power };
    }

}
