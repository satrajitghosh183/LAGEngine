#pragma once
#include <vector>
#include "Particle3D.hpp"
#include "Constraint3D.hpp"

namespace engine::physics {

    /**
     * @brief Cloth solver: manages particle grid and constraints
     *        to simulate cloth dynamics using constraint satisfaction.
     */
    class ClothSolver {
    public:
        std::vector<Particle3D> particles;
        std::vector<Constraint3D> constraints;

        /**
         * @brief Update all particles using Verlet integration.
         * @param dt Time step
         * @param acceleration Global acceleration (e.g., gravity)
         */
        void update(float dt, const glm::vec3& acceleration) {
            for (auto& p : particles) {
                p.update(dt, acceleration);
            }
        }

        /**
         * @brief Apply all constraints multiple times for stability.
         * @param iterations Number of solver iterations (e.g., 10–20)
         */
        void solve(int iterations = 20) {
            for (int i = 0; i < iterations; ++i) {
                for (const auto& c : constraints) {
                    c.satisfy(particles);
                }
            }
        }

        /**
         * @brief Add a particle to the cloth grid.
         */
        void addParticle(const glm::vec3& position, const glm::vec3& velocity = {0.0f, 0.0f, 0.0f}, bool locked = false) {
            Particle3D p(position, velocity);
            p.locked = locked;
            particles.push_back(p);
        }

        /**
         * @brief Add a constraint between two particle indices.
         */
        void addConstraint(int i1, int i2, float restLength) {
            constraints.emplace_back(i1, i2, restLength);
        }
    };

} // namespace engine::physics
