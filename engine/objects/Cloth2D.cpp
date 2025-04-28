
#include "engine/objects/Cloth2D.hpp"
#include "engine/objects/Ball2D.hpp"
#include <cmath>

namespace engine::objects {

    using namespace physics;

    Cloth2D::Cloth2D(int w, int h, float s, const sf::Vector2f& origin)
        : width(w), height(h), spacing(s) {
        particles.resize(width * height);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                sf::Vector2f pos = origin + sf::Vector2f(x * spacing, y * spacing);
                bool locked = (y == 0 && (x % 5 == 0));
                particles[y * width + x] = Particle(pos, {0, 0});
                particles[y * width + x].locked = locked;

                if (x > 0)
                    constraints.emplace_back((y * width + x - 1), (y * width + x), spacing);
                if (y > 0)
                    constraints.emplace_back(((y - 1) * width + x), (y * width + x), spacing);
            }
        }
    }

    void Cloth2D::update(float dt, const sf::Vector2f& gravity, int iterations) {
        for (auto& p : particles) p.update(dt, gravity);
        for (int i = 0; i < iterations; ++i)
            for (auto& c : constraints) c.satisfy(particles);

        if (projectiles) {
            checkCollisionAndTear();
        }
    }

    void Cloth2D::update(float dt) {
        update(dt, {0.f, 980.f}, 5);
    }

    void Cloth2D::render(sf::RenderWindow& window) {
        for (auto& c : constraints) {
            const auto& p1 = particles[c.p1Index].pos;
            const auto& p2 = particles[c.p2Index].pos;
            sf::Vertex line[] = { sf::Vertex(p1), sf::Vertex(p2) };
            window.draw(line, 2, sf::Lines);
        }
    }

    void Cloth2D::setProjectiles(std::vector<Ball2D*>* proj) { // ✅ Fix: use pointer
        projectiles = proj;
    }

    void Cloth2D::checkCollisionAndTear() {
        if (!projectiles) return;

        for (auto* ball : *projectiles) {
            sf::Vector2f ballPos = ball->particle.pos;
            float radius = ball->radius;

            constraints.erase(std::remove_if(constraints.begin(), constraints.end(),
                [&](const Constraint2D& c) {
                    const auto& p1 = particles[c.p1Index].pos;
                    const auto& p2 = particles[c.p2Index].pos;
                    return (std::hypot(p1.x - ballPos.x, p1.y - ballPos.y) < radius) ||
                           (std::hypot(p2.x - ballPos.x, p2.y - ballPos.y) < radius);
                }),
                constraints.end());
        }
    }

}
