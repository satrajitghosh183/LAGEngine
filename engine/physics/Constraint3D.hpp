// #pragma once
// #include <vector>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include "Particle3D.hpp"

// namespace engine::physics {

//     /**
//      * @brief Represents a distance constraint between two 3D particles.
//      *        Used in cloth, rope, and soft body simulations.
//      */
//     class Constraint3D {
//     public:
//         int p1Index;         // Index of the first particle in the array
//         int p2Index;         // Index of the second particle
//         float restLength;    // Target distance between the two particles

//         /**
//          * @brief Constructor for the constraint.
//          * @param index1 Index of the first particle
//          * @param index2 Index of the second particle
//          * @param rest Target distance between the particles
//          */
//         Constraint3D(int index1, int index2, float rest)
//             : p1Index(index1), p2Index(index2), restLength(rest) {}

//         /**
//          * @brief Satisfies the constraint by adjusting particle positions.
//          *
//          * @param particles Reference to the array of Particle3D objects.
//          *        Assumes both p1Index and p2Index are valid indices.
//          */
//         void satisfy(std::vector<Particle3D>& particles) const;
//     };

// } // namespace engine::physics
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Particle3D.hpp"

namespace engine::physics {

    class Constraint3D {
    public:
        int p1Index, p2Index;
        float restLength;

        Constraint3D(int index1, int index2, float rest)
            : p1Index(index1), p2Index(index2), restLength(rest) {}

        void satisfy(std::vector<Particle3D>& particles) const;

        // Check if the constraint is satisfied and return true if it is
        // and false if it is not. This can be used to check if the constraint
        // bool satisfyAndCheckTear(std::vector<Particle3D>& particles, float tearThreshold) const;
        bool satisfyAndCheckTear(std::vector<Particle3D*>& particles, float tearThreshold) const;

    };

}
