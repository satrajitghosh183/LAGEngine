// engine/scene/SceneManager3D.cpp
#include "engine/scene/SceneManager3D.hpp"
#include "engine/graphics/Shader.hpp"

namespace engine::scene {

    Scene3D* SceneManager3D::get() {
        return &scene;
    }

    void SceneManager3D::update(float dt) {
        scene.update(dt);
    }

    void SceneManager3D::render(const engine::graphics::Shader& shader) {
        scene.render(shader);
    }

} // namespace engine::scene
