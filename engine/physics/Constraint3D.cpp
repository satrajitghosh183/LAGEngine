// engine/physics/Constraint3D.cpp
#include "engine/physics/Constraint3D.hpp"

namespace engine::physics {

    void Constraint3D::satisfy(std::vector<Particle3D>& particles) const {
        Particle3D& p1 = particles[p1Index];
        Particle3D& p2 = particles[p2Index];

        glm::vec3 delta = p2.pos - p1.pos;
        float dist = glm::length(delta);
        if (dist == 0.0f) return;

        float diff = (dist - restLength) / dist;
        glm::vec3 correction = delta * 0.5f * diff;

        if (!p1.locked && !p2.locked) {
            p1.pos += correction;
            p2.pos -= correction;
        } else if (p1.locked && !p2.locked) {
            p2.pos -= correction * 2.0f;
        } else if (!p1.locked && p2.locked) {
            p1.pos += correction * 2.0f;
        }
    }

} // namespace engine::physics