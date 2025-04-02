#pragma once
#include <vector>
#include "Particle3D.hpp"
#include "Constraint3D.hpp"

namespace engine::physics {

    /**
     * @brief Soft body system (generalized physics blob or deformable object)
     */
    class SoftBodySystem {
    public:
        std::vector<Particle3D> particles;
        std::vector<Constraint3D> constraints;

        /**
         * @brief Update all particles with Verlet integration.
         */
        void update(float dt, const glm::vec3& acceleration) {
            for (auto& p : particles)
                p.update(dt, acceleration);
        }

        /**
         * @brief Solve constraints for stability and shape preservation.
         */
        void solveConstraints(int iterations = 10) {
            for (int i = 0; i < iterations; ++i) {
                for (auto& c : constraints)
                    c.satisfy(particles);
            }
        }

        /**
         * @brief Add a particle to the system.
         */
        void addParticle(const glm::vec3& position, const glm::vec3& velocity = glm::vec3(0), bool locked = false) {
            Particle3D p(position, velocity);
            p.locked = locked;
            particles.push_back(p);
        }

        /**
         * @brief Create a soft connection (constraint) between two particles.
         */
        void connect(int i1, int i2, float restLength) {
            constraints.emplace_back(i1, i2, restLength);
        }
    };

} // namespace engine::physics
