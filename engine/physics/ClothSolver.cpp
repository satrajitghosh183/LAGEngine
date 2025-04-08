// engine/physics/ClothSolver.cpp
#include "engine/physics/ClothSolver.hpp"

namespace engine::physics {

    void ClothSolver::update(float dt, const glm::vec3& acceleration) {
        for (auto& p : particles) {
            p.update(dt, acceleration);
        }
    }

    void ClothSolver::solve(int iterations) {
        for (int i = 0; i < iterations; ++i) {
            for (const auto& c : constraints) {
                c.satisfy(particles);
            }
        }
    }

    void ClothSolver::addParticle(const glm::vec3& position, const glm::vec3& velocity, bool locked) {
        Particle3D p(position, velocity);
        p.locked = locked;
        particles.push_back(p);
    }

    void ClothSolver::addConstraint(int i1, int i2, float restLength) {
        constraints.emplace_back(i1, i2, restLength);
    }

} // namespace engine::physics