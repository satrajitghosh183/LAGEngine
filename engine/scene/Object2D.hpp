
#pragma once
#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine::scene {

    class Object2D {
    public:
        virtual ~Object2D() = default;

        virtual void update(float dt) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

        bool active = true;
        bool visible = true; // ✅ Add this to fix Scene2D checks
    };

}
