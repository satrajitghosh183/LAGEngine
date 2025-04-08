#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "engine/physics/Particle.hpp"

namespace engine::physics {

    struct Constraint2D {
        int p1Index, p2Index;
        float restLength;

        Constraint2D(int i1, int i2, float length)
            : p1Index(i1), p2Index(i2), restLength(length) {}

        void satisfy(std::vector<Particle>& particles);
    };

}
