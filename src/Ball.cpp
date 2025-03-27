#include "Ball.hpp"
#include "math.hpp"

Ball::Ball(const sf::Vector2f& position, const sf::Vector2f& initialVelocity, float radius)
    : particle(position, initialVelocity), radius(radius)
{}

void Ball::update(float dt, const sf::Vector2f& acceleration, const sf::RenderWindow& window) {
    particle.update(dt, acceleration);

    // Improved boundary collision handling with increased restitution.
    sf::Vector2u size = window.getSize();
    const float restitution = -0.95f;  // Increased restitution for more bounce.

    if (particle.pos.x - radius < 0) {
        particle.pos.x = radius;
        particle.oldPos.x = particle.pos.x + (particle.pos.x - particle.oldPos.x) * restitution;
    }
    if (particle.pos.x + radius > size.x) {
        particle.pos.x = size.x - radius;
        particle.oldPos.x = particle.pos.x + (particle.pos.x - particle.oldPos.x) * restitution;
    }
    if (particle.pos.y - radius < 0) {
        particle.pos.y = radius;
        particle.oldPos.y = particle.pos.y + (particle.pos.y - particle.oldPos.y) * restitution;
    }
    if (particle.pos.y + radius > size.y) {
        particle.pos.y = size.y - radius;
        particle.oldPos.y = particle.pos.y + (particle.pos.y - particle.oldPos.y) * restitution;
    }
}

void Ball::draw(sf::RenderWindow& window) const {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(particle.pos);
    circle.setFillColor(sf::Color::Cyan);
    window.draw(circle);
}
