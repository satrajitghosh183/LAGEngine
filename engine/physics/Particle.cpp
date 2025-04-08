#include "engine/physics/Particle.hpp"

namespace engine::physics {

    Particle::Particle(const sf::Vector2f& position) : pos(position), oldPos(position) {}

    Particle::Particle(const sf::Vector2f& position, const sf::Vector2f& velocity)
        : pos(position), oldPos(position - velocity) {}

    void Particle::update(float dt, const sf::Vector2f& acceleration) {
        if (locked) return;
        sf::Vector2f temp = pos;
        pos += pos - oldPos + acceleration * dt * dt;
        oldPos = temp;
    }

    void Particle::constrainToWindow(const sf::RenderWindow& window) {
        if (pos.x < 0) pos.x = 0;
        if (pos.y < 0) pos.y = 0;
        if (pos.x > window.getSize().x) pos.x = window.getSize().x;
        if (pos.y > window.getSize().y) pos.y = window.getSize().y;
    }

    void Particle::draw(sf::RenderWindow& window) const {
        sf::CircleShape circle(2.f);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(pos - sf::Vector2f(2.f, 2.f));
        window.draw(circle);
    }

}
