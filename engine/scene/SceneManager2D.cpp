// #include "engine/scene/SceneManager.hpp"

// namespace engine::scene {

//     SceneManager::SceneManager() {
//         scene2D = std::make_unique<Scene2D>();
//         scene3D = std::make_unique<Scene3D>();
//     }

//     Scene2D* SceneManager::get2D() {
//         return scene2D.get();
//     }

//     Scene3D* SceneManager::get3D() {
//         return scene3D.get();
//     }

//     void SceneManager::update2D(float dt) {
//         if (scene2D) scene2D->update(dt);
//     }

//     void SceneManager::update3D(float dt) {
//         if (scene3D) scene3D->update(dt);
//     }

//     void SceneManager::render2D(sf::RenderWindow& window) {
//         if (scene2D) scene2D->render(window);
//     }

//     void SceneManager::render3D(const engine::graphics::Shader& shader) {
//         if (scene3D) scene3D->render(shader);
//     }

// } // namespace engine::scene
// engine/scene/SceneManager2D.cpp
#include "engine/scene/SceneManager2D.hpp"

namespace engine::scene {

    Scene2D* SceneManager2D::get2D() {
        return &scene;
    }

    void SceneManager2D::update2D(float dt) {
        scene.update(dt);
    }

    void SceneManager2D::render2D(sf::RenderWindow& window) {
        scene.render(window);
    }

} // namespace engine::scene
