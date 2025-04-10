// engine/physics/PhysicsWorld3D.cpp
#include "engine/physics/PhysicsWorld3D.hpp"

namespace engine::physics {

    void PhysicsWorld3D::update(float dt, const glm::vec3& acceleration) {
        // Integrate all particles
        for (auto* p : particles)
            p->update(dt, acceleration, damping);

        // Apply constraints with optional tearing
        for (int i = 0; i < 10; ++i) {
            for (auto it = constraints.begin(); it != constraints.end(); ) {
                if ((*it)->satisfyAndCheckTear(particles, tearThreshold)) {
                    it = constraints.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

} // namespace engine::physics
