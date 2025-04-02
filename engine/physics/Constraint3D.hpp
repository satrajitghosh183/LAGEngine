#pragma once
#include <glm/glm.hpp>
#include "Particle3D.hpp"

namespace engine::physics {

    /**
     * @brief Represents a distance constraint between two 3D particles.
     *        Used in cloth, rope, and soft body simulations.
     */
    class Constraint3D {
    public:
        int p1Index;         // Index of the first particle in the array
        int p2Index;         // Index of the second particle
        float restLength;    // Target distance between the two particles

        /**
         * @brief Constructor for the constraint.
         * @param index1 Index of the first particle
         * @param index2 Index of the second particle
         * @param rest Target distance between the particles
         */
        Constraint3D(int index1, int index2, float rest)
            : p1Index(index1), p2Index(index2), restLength(rest) {}

        /**
         * @brief Satisfies the constraint by adjusting particle positions.
         * 
         * @param particles Reference to the array of Particle3D objects.
         *        Assumes both p1Index and p2Index are valid indices.
         */
        void satisfy(std::vector<Particle3D>& particles) const {
            Particle3D& p1 = particles[p1Index];
            Particle3D& p2 = particles[p2Index];

            glm::vec3 delta = p2.pos - p1.pos;
            float dist = glm::length(delta);

            if (dist == 0.0f) return; // Avoid divide by zero

            float diff = (dist - restLength) / dist;
            glm::vec3 correction = delta * 0.5f * diff;

            // Apply corrections based on whether the particles are locked
            if (!p1.locked && !p2.locked) {
                p1.pos += correction;
                p2.pos -= correction;
            } else if (p1.locked && !p2.locked) {
                p2.pos -= correction * 2.0f;
            } else if (!p1.locked && p2.locked) {
                p1.pos += correction * 2.0f;
            }
        }
    };

} // namespace engine::physics
