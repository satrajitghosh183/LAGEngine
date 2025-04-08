#pragma once
#include <vector>
#include "Object2D.hpp"
#include "Object3D.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace engine::scene {

    class Scene {
    public:
        std::vector<Object2D*> objects2D;
        std::vector<Object3D*> objects3D;

        Scene() = default;

        void add(Object2D* obj);
        void add(Object3D* obj);

        void update(float dt);

        void render(sf::RenderWindow& window);
        void render(const engine::graphics::Shader& shader);
    };

} // namespace engine::scene
