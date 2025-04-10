// engine/physics/PhysicsWorld3D.hpp
#pragma once
#include "Particle3D.hpp"
#include "Constraint3D.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace engine::physics {

    class PhysicsWorld3D {
    public:
        std::vector<Particle3D*> particles;
        std::vector<Constraint3D*> constraints;

        float damping = 0.98f;
        float tearThreshold = 5.0f;

        void addParticle(Particle3D* p) {
            particles.push_back(p);
        }

        void addConstraint(Constraint3D* c) {
            constraints.push_back(c);
        }

        void update(float dt, const glm::vec3& acceleration);
    };

} // namespace engine::physics
