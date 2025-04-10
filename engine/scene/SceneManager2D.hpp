// #pragma once
// #include <memory>
// #include "Scene2D.hpp"
// #include "Scene3D.hpp"
// #include <SFML/Graphics.hpp>
// #include "engine/graphics/Shader.hpp"

// namespace engine::scene {

//     class SceneManager {
//     private:
//         std::unique_ptr<Scene2D> scene2D;
//         std::unique_ptr<Scene3D> scene3D;

//     public:
//         SceneManager();

//         Scene2D* get2D();
//         Scene3D* get3D();

//         void update2D(float dt);
//         void update3D(float dt);

//         void render2D(sf::RenderWindow& window);
//         void render3D(const engine::graphics::Shader& shader);
//     };

// } // namespace engine::scene
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
