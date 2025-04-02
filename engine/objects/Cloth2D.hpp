// engine/objects/Cloth2D.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "engine/physics/Particle.hpp"
#include "engine/scene/Object2D.hpp"

namespace engine::objects {

    struct Constraint2D {
        int p1, p2;
        float restLength;
    };

    class Cloth2D : public engine::scene::Object2D {
    public:
        std::vector<engine::physics::Particle> particles;
        std::vector<Constraint2D> constraints;
        int width, height;
        float spacing;

        Cloth2D(int w, int h, float s, const sf::Vector2f& origin)
            : width(w), height(h), spacing(s) {
            for (int j = 0; j < height; ++j) {
                for (int i = 0; i < width; ++i) {
                    sf::Vector2f pos = origin + sf::Vector2f(i * spacing, j * spacing);
                    engine::physics::Particle p(pos);
                    if (j == 0) p.lock();
                    particles.push_back(p);
                }
            }

            for (int j = 0; j < height; ++j) {
                for (int i = 0; i < width; ++i) {
                    int index = j * width + i;
                    if (i < width - 1)
                        constraints.push_back({index, index + 1, spacing});
                    if (j < height - 1)
                        constraints.push_back({index, index + width, spacing});
                }
            }
        }

        void update(float dt, const sf::Vector2f& gravity, int iterations) {
            for (auto& p : particles)
                p.update(dt, gravity);

            for (int k = 0; k < iterations; ++k) {
                for (auto& c : constraints) {
                    auto& p1 = particles[c.p1];
                    auto& p2 = particles[c.p2];
                    sf::Vector2f delta = p2.pos - p1.pos;
                    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
                    float diff = (dist - c.restLength) / (dist + 1e-6f);
                    if (!p1.locked && !p2.locked) {
                        p1.pos += delta * 0.5f * diff;
                        p2.pos -= delta * 0.5f * diff;
                    } else if (!p1.locked) {
                        p1.pos += delta * diff;
                    } else if (!p2.locked) {
                        p2.pos -= delta * diff;
                    }
                }
            }
        }

        void update(float) override {}

        void render(sf::RenderWindow& window) override {
            for (const auto& p : particles) p.draw(window);
        }
    };

} // namespace engine::objects
