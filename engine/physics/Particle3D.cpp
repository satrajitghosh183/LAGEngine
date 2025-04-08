// Particle3D.cpp
#include "engine/physics/Particle3D.hpp"

namespace engine::physics {

    Particle3D::Particle3D(const glm::vec3& position)
        : pos(position), oldPos(position) {}

    Particle3D::Particle3D(const glm::vec3& position, const glm::vec3& initialVelocity)
        : pos(position), oldPos(position - initialVelocity) {}

    void Particle3D::update(float dt, const glm::vec3& acceleration, float damping) {
        if (locked) return;
        glm::vec3 velocity = (pos - oldPos) * damping;
        oldPos = pos;
        pos += velocity + acceleration * dt * dt;
    }

} // namespace engine::physics