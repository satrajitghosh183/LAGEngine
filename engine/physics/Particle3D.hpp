#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine::physics {

    // A 3D particle for physics simulation (Verlet integration)
    class Particle3D {
    public:
        glm::vec3 pos;
        glm::vec3 oldPos;
        bool locked = false;

        Particle3D(const glm::vec3& position);
        Particle3D(const glm::vec3& position, const glm::vec3& initialVelocity);

        void update(float dt, const glm::vec3& acceleration, float damping = 0.99f);
    };

} // namespace engine::physics