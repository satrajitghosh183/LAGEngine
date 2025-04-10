#pragma once
#include "Scene3D.hpp"

namespace engine::scene {

    class SceneManager3D {
    private:
        Scene3D scene;

    public:
        Scene3D* get() { return &scene; }

        void update(float dt) { scene.update(dt); }

        void render(const engine::graphics::Shader& shader) { scene.render(shader); }
    };

} // namespace engine::scene
