// engine/scene/SceneManager.hpp
#pragma once
#include <memory>
#include "Scene.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace engine::scene {

    /**
     * @brief Manages switching between scenes, pausing, and lifecycle control.
     */
    class SceneManager {
    private:
        std::unique_ptr<Scene> activeScene;

    public:
        SceneManager();
        Scene* get();
        void update(float dt);
        void render(sf::RenderWindow& window);
        void render(const engine::graphics::Shader& shader);
    };

} // namespace engine::scene
