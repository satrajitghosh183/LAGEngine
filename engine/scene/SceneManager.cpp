#include "engine/scene/SceneManager.hpp"

namespace engine::scene {
    SceneManager::SceneManager() {
        activeScene = std::make_unique<Scene>();
    }

    Scene* SceneManager::get() {
        return activeScene.get();
    }

    void SceneManager::update(float dt) {
        if (activeScene) activeScene->update(dt);
    }

    void SceneManager::render(sf::RenderWindow& window) {
        if (activeScene) activeScene->render(window);
    }

    void SceneManager::render(const engine::graphics::Shader& shader) {
        if (activeScene) activeScene->render(shader);
    }
} // namespace engine::scene
