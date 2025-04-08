// engine/objects/Ball2D.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "engine/physics/Particle.hpp"
#include "engine/scene/Object2D.hpp"

namespace engine::objects {

    class Ball2D : public engine::scene::Object2D {
    public:
        engine::physics::Particle particle;
        float radius;
        float restitution;

        Ball2D(const sf::Vector2f& position,
               const sf::Vector2f& velocity,
               float r,
               float rest = 0.8f);

        void update(float dt, const sf::Vector2f& acceleration, const sf::RenderWindow& window);
        void update(float) override;
        void render(sf::RenderWindow& window) override;
    };

} // namespace engine::objects
