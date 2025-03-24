#pragma once
#include <vector>
#include "Particle.hpp"
#include <SFML/Graphics.hpp>

// A constraint connecting two particles.
struct Constraint {
    int p1;           // Index of the first particle.
    int p2;           // Index of the second particle.
    float restLength; // Resting distance between the two particles.
};

class Cloth {
public:
    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    int clothWidth;
    int clothHeight;

    // Create a cloth grid starting at 'origin' with given spacing.
    Cloth(int width, int height, float spacing, const sf::Vector2f& origin);

    // Update the cloth simulation.
    // dt: delta time; acceleration: external acceleration (e.g. gravity);
    // iterations: number of constraint relaxation iterations.
    void update(float dt, const sf::Vector2f& acceleration, int iterations);

    // Draw the cloth (constraints and particles).
    void draw(sf::RenderWindow& window);
};
