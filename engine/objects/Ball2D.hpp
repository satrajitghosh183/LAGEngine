
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
        sf::Vector2f gravity = {0.f, 980.f}; // ✅ gravity added internally

        Ball2D(const sf::Vector2f& position,
               const sf::Vector2f& velocity,
               float r,
               float rest = 0.8f);

        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
    };

}
