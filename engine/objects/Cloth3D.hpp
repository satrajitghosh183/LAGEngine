#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "engine/physics/Particle3D.hpp"
#include "engine/physics/Constraint3D.hpp"
#include "engine/graphics/Mesh.hpp"
#include "engine/scene/SceneManager3D.hpp"
#include "engine/scene/Object3D.hpp"
#include "engine/graphics/Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace engine::objects {

    class Cloth3D : public engine::scene::Object3D {
    public:
        std::vector<engine::physics::Particle3D> particles;
        std::vector<engine::physics::Constraint3D> constraints;
        engine::graphics::Mesh mesh;
        int width, height;
        float spacing;
        engine::scene::SceneManager3D& sceneManagerRef;
        // Cloth3D(int w, int h, float s, const glm::vec3& origin);
        Cloth3D(int w, int h, float s, const glm::vec3& origin, engine::scene::SceneManager3D& sceneManager);


        void update(float) override;
        void update(float dt, const glm::vec3& acceleration, int iterations);
        void render(const engine::graphics::Shader& shader) override;

    private:
        void updateMesh();
    };

} // namespace engine::objects