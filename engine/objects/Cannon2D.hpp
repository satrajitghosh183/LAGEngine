// engine/objects/Cannon2D.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "engine/scene/Object2D.hpp"

namespace engine::objects {

    class Cannon2D : public engine::scene::Object2D {
    public:
        sf::Vector2f position;
        float angle = -90.0f; // Facing upward initially
        float power = 800.0f; // Firing speed

        Cannon2D(const sf::Vector2f& pos);

        void rotate(float degrees);
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;

        sf::Vector2f getFiringVelocity() const;
    };

}
