
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
