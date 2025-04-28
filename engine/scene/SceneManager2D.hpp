#pragma once
#include "Scene2D.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace engine::scene {

    class SceneManager2D {
    private:
        Scene2D scene;

    public:
        Scene2D* get2D();                                // Declaration
        void update2D(float dt);                         // Declaration
        void render2D(sf::RenderWindow& window);         // Declaration
    };

} // namespace engine::scene
