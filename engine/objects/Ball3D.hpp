// #pragma once
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include "engine/physics/Particle3D.hpp"
// #include "engine/scene/Object3D.hpp"
// #include "engine/graphics/Mesh.hpp"
// #include "engine/graphics/Shader.hpp"

// namespace engine::objects {

//     class Ball3D : public engine::scene::Object3D {
//     public:
//         engine::physics::Particle3D particle;
//         float radius;
//         float restitution;
//         engine::graphics::Mesh mesh;

//         Ball3D(const glm::vec3& pos,
//                const glm::vec3& velocity,
//                float r,
//                float rest = 0.95f);

//         void update(float) override;

//         void update(float dt, const glm::vec3& acceleration,
//                     const glm::vec3& minBounds, const glm::vec3& maxBounds);

//         void render(const engine::graphics::Shader& shader) override;
//     };

// } // namespace engine::objects
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/physics/Particle3D.hpp"
#include "engine/scene/Object3D.hpp"
#include "engine/graphics/Mesh.hpp"
#include "engine/graphics/Shader.hpp"
#include "engine/objects/Cloth3D.hpp" // ✅ added for interaction

namespace engine::objects {

    class Ball3D : public engine::scene::Object3D {
    public:
        engine::physics::Particle3D particle;
        float radius;
        float restitution;
        engine::graphics::Mesh mesh;

        Ball3D(const glm::vec3& pos,
               const glm::vec3& velocity,
               float r,
               float rest = 0.95f);

        void update(float) override;
        void update(float dt, const glm::vec3& acceleration,
                    const glm::vec3& minBounds, const glm::vec3& maxBounds);
        void render(const engine::graphics::Shader& shader) override;

        // ✅ New: Cloth interaction logic
        void interactWithCloth(Cloth3D* cloth, float forceMultiplier = 1.0f);
    };

}
