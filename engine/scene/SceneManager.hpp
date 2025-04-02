
// engine/scene/SceneManager.hpp
#pragma once
#include <memory>
#include "Scene.hpp"

namespace engine::scene {

    /**
     * @brief Manages switching between scenes, pausing, and lifecycle control.
     */
    class SceneManager {
    private:
        std::unique_ptr<Scene> activeScene;

    public:
        SceneManager() {
            activeScene = std::make_unique<Scene>();
        }

        Scene* get() {
            return activeScene.get();
        }

        void update(float dt) {
            if (activeScene) activeScene->update(dt);
        }

        void render(sf::RenderWindow& window) {
            if (activeScene) activeScene->render(window);
        }

        void render(const engine::graphics::Shader& shader) {
            if (activeScene) activeScene->render(shader);
        }
    };

} // namespace engine::scene
