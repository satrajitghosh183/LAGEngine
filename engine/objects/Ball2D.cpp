
// engine/objects/Ball2D.cpp
#include "engine/objects/Ball2D.hpp"

namespace engine::objects {

    Ball2D::Ball2D(const sf::Vector2f& position,
                   const sf::Vector2f& velocity,
                   float r,
                   float rest)
        : particle(position, velocity), radius(r), restitution(rest) {}

    void Ball2D::update(float dt) {
        if (!active) return;

        particle.update(dt, gravity);

        // Soft delete if out of bounds
        if (particle.pos.y > 1000 || particle.pos.x < -100 || particle.pos.x > 1400) {
            active = false;
            visible = false;
        }
    }

    void Ball2D::render(sf::RenderWindow& window) {
        if (!visible) return;
        sf::CircleShape shape(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(particle.pos);
        shape.setFillColor(sf::Color::White);
        window.draw(shape);
    }

}
