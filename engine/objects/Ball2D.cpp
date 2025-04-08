// engine/objects/Ball2D.cpp
#include "engine/objects/Ball2D.hpp"

namespace engine::objects {

    Ball2D::Ball2D(const sf::Vector2f& position,
                   const sf::Vector2f& velocity,
                   float r,
                   float rest)
        : particle(position, velocity), radius(r), restitution(rest) {}

    void Ball2D::update(float dt, const sf::Vector2f& acceleration, const sf::RenderWindow& window) {
        particle.update(dt, acceleration);
        particle.constrainToWindow(window);
    }

    void Ball2D::update(float) {
        // Stub for Object2D interface
    }

    void Ball2D::render(sf::RenderWindow& window) {
        sf::CircleShape shape(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(particle.pos);
        shape.setFillColor(sf::Color::White);
        window.draw(shape);
    }

} // namespace engine::objects
