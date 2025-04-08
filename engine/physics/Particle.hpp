#pragma once
#include <SFML/Graphics.hpp>

namespace engine::physics {

    class Particle {
    public:
        sf::Vector2f pos;
        sf::Vector2f oldPos;
        bool locked = false;

        Particle() = default;
        Particle(const sf::Vector2f& position);
        Particle(const sf::Vector2f& position, const sf::Vector2f& velocity);

        void update(float dt, const sf::Vector2f& acceleration);
        void constrainToWindow(const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window) const;
    };

}
