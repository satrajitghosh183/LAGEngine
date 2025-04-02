// engine/physics/VerletSystem.hpp
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

namespace engine::physics {

    // A simple 2D particle system using Verlet physics
    class VerletSystem {
    public:
        std::vector<Particle> particles;

        VerletSystem() = default;

        void addParticle(const sf::Vector2f& position);
        void addParticle(const sf::Vector2f& position, const sf::Vector2f& initialVelocity);
        void update(float dt, const sf::Vector2f& acceleration, const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
    };

} // namespace engine::physics
