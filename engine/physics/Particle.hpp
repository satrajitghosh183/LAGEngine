// engine/physics/Particle.hpp
#pragma once
#include <SFML/Graphics.hpp>

namespace engine::physics {

    // A 2D particle using Verlet integration
    class Particle {
    public:
        sf::Vector2f pos;
        sf::Vector2f oldPos;
        bool locked = false;

        Particle(const sf::Vector2f& position);
        Particle(const sf::Vector2f& position, const sf::Vector2f& initialVelocity);

        void update(float dt, const sf::Vector2f& acceleration);
        void constrainToWindow(const sf::RenderWindow& window);
        void lock();
        void unlock();
        void draw(sf::RenderWindow& window) const;
    };

} // namespace engine::physics
