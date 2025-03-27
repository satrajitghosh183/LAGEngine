#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

class Ball {
public:
    Particle particle; // Underlying particle for Verlet integration.
    float radius;

    Ball(const sf::Vector2f& position, const sf::Vector2f& initialVelocity, float radius);

    // Update ball physics and handle boundary collisions.
    void update(float dt, const sf::Vector2f& acceleration, const sf::RenderWindow& window);

    // Render the ball.
    void draw(sf::RenderWindow& window) const;
};
