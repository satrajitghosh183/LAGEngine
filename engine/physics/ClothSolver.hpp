#pragma once
#include <vector>
#include "Particle3D.hpp"
#include "Constraint3D.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace engine::physics {

    /**
     * @brief Cloth solver: manages particle grid and constraints
     *        to simulate cloth dynamics using constraint satisfaction.
     */
    class ClothSolver {
    public:
        std::vector<Particle3D> particles;
        std::vector<Constraint3D> constraints;
        

        ClothSolver() = default;

        /**
         * @brief Update all particles using Verlet integration.
         * @param dt Time step
         * @param acceleration Global acceleration (e.g., gravity)
         */
        void update(float dt, const glm::vec3& acceleration);

        /**
         * @brief Apply all constraints multiple times for stability.
         * @param iterations Number of solver iterations (e.g., 10–20)
         */
        void solve(int iterations = 20);

        /**
         * @brief Add a particle to the cloth grid.
         */
        void addParticle(const glm::vec3& position, const glm::vec3& velocity = {0.0f, 0.0f, 0.0f}, bool locked = false);

        /**
         * @brief Add a constraint between two particle indices.
         */
        void addConstraint(int i1, int i2, float restLength);
    };

} // namespace engine::physics