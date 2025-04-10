// engine/physics/Constraint2D.cpp
#include "engine/physics/Constraint2D.hpp"
#include <cmath> // ✅ This gives you std::sqrt

namespace engine::physics {

    void Constraint2D::satisfy(std::vector<Particle>& particles) {
        Particle& p1 = particles[p1Index];
        Particle& p2 = particles[p2Index];

        sf::Vector2f delta = p2.pos - p1.pos;
        float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        if (dist == 0.0f) return;

        float diff = (dist - restLength) / dist;
        sf::Vector2f correction = delta * 0.5f * diff;

        if (!p1.locked && !p2.locked) {
            p1.pos += correction;
            p2.pos -= correction;
        } else if (p1.locked && !p2.locked) {
            p2.pos -= correction * 2.0f;
        } else if (!p1.locked && p2.locked) {
            p1.pos += correction * 2.0f;
        }
    }

}
