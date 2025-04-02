// engine/scene/Scene.hpp
#pragma once
#include <vector>
#include "Object2D.hpp"
#include "Object3D.hpp"

namespace engine::scene {

    /**
     * @brief Scene holds and manages all active 2D and 3D objects.
     */
    class Scene {
    public:
        std::vector<Object2D*> objects2D;
        std::vector<Object3D*> objects3D;

        Scene() = default;

        // Add a 2D object to the scene
        void add(Object2D* obj) {
            objects2D.push_back(obj);
        }

        // Add a 3D object to the scene
        void add(Object3D* obj) {
            objects3D.push_back(obj);
        }

        // Update all objects
        void update(float dt) {
            for (auto* obj : objects2D)
                if (obj && obj->active) obj->update(dt);

            for (auto* obj : objects3D)
                if (obj) obj->update(dt);
        }

        // Render all objects
        void render(sf::RenderWindow& window) {
            for (auto* obj : objects2D)
                if (obj && obj->active) obj->render(window);
        }

        void render(const engine::graphics::Shader& shader) {
            for (auto* obj : objects3D)
                if (obj && obj->visible) obj->render(shader);
        }
    };

} // namespace engine::scene
