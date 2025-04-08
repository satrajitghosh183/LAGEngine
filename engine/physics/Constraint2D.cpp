#include "engine/physics/Constraint2D.hpp"
#include <cmath>

namespace engine::physics {

    void Constraint2D::satisfy(std::vector<Particle>& particles) {
        Particle& p1 = particles[p1Index];
        Particle& p2 = particles[p2Index];

        sf::Vector2f delta = p2.pos - p1.pos;
        float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        float diff = (dist - restLength) / (dist + 1e-6f);

        if (p1.locked && p2.locked) return;

        if (!p1.locked) p1.pos += 0.5f * diff * delta;
        if (!p2.locked) p2.pos -= 0.5f * diff * delta;
    }

}
