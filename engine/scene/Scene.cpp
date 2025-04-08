#include "engine/scene/Scene.hpp"

namespace engine::scene {

    void Scene::add(Object2D* obj) {
        objects2D.push_back(obj);
    }

    void Scene::add(Object3D* obj) {
        objects3D.push_back(obj);
    }

    void Scene::update(float dt) {
        for (auto* obj : objects2D)
            if (obj && obj->active)
                obj->update(dt);

        for (auto* obj : objects3D)
            if (obj)
                obj->update(dt);
    }

    void Scene::render(sf::RenderWindow& window) {
        for (auto* obj : objects2D)
            if (obj && obj->active)
                obj->render(window);
    }

    void Scene::render(const engine::graphics::Shader& shader) {
        for (auto* obj : objects3D)
            if (obj && obj->visible)
                obj->render(shader);
    }

} // namespace engine::scene
