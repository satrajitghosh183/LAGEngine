#pragma once
#include <SFML/Graphics.hpp>

namespace engine::scene {

    /**
     * @brief Base class for any 2D object in the scene.
     *        Inherit from this to create game objects like Ball2D, Platform2D, etc.
     */
    class Object2D {
    public:
        virtual ~Object2D() = default;

        // Called every frame to update logic.
        virtual void update(float dt) = 0;

        // Called every frame to render.
        virtual void render(sf::RenderWindow& window) = 0;

        // Optional: object can be marked inactive
        bool active = true;
    };

} // namespace engine::scene
