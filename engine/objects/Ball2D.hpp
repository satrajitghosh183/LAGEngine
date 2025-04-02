// engine/objects/Ball2D.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "engine/physics/Particle.hpp"
#include "engine/scene/Object2D.hpp"

namespace engine::objects {

    class Ball2D : public engine::scene::Object2D {
    public:
        engine::physics::Particle particle;
        float radius;
        float restitution;

        Ball2D(const sf::Vector2f& position,
               const sf::Vector2f& velocity,
               float r,
               float rest = 0.8f)
            : particle(position, velocity), radius(r), restitution(rest) {}

        void update(float dt, const sf::Vector2f& acceleration, const sf::RenderWindow& window) {
            particle.update(dt, acceleration);
            particle.constrainToWindow(window);
        }

        void update(float) override {}

        void render(sf::RenderWindow& window) override {
            sf::CircleShape shape(radius);
            shape.setOrigin(radius, radius);
            shape.setPosition(particle.pos);
            shape.setFillColor(sf::Color::White);
            window.draw(shape);
        }
    };

} // namespace engine::objects


// engine/objects/Ball3D.hpp
#pragma once
#include <glm/glm.hpp>
#include "engine/physics/Particle3D.hpp"
#include "engine/scene/Object3D.hpp"
#include "engine/graphics/Mesh.hpp"
#include "engine/graphics/Shader.hpp"

namespace engine::objects {

    class Ball3D : public engine::scene::Object3D {
    public:
        engine::physics::Particle3D particle;
        float radius;
        float restitution;
        engine::graphics::Mesh mesh;

        Ball3D(const glm::vec3& pos,
               const glm::vec3& velocity,
               float r,
               float rest = 0.95f)
            : particle(pos, velocity), radius(r), restitution(rest) {
            // Generate sphere mesh externally and assign
            mesh.vertices.push_back(pos); // Replace with proper sphere mesh
            mesh.upload();
        }

        void update(float) override {}

        void update(float dt, const glm::vec3& acceleration,
                    const glm::vec3& minBounds, const glm::vec3& maxBounds) {
            particle.update(dt, acceleration);

            for (int i = 0; i < 3; ++i) {
                if (particle.pos[i] - radius < minBounds[i]) {
                    particle.pos[i] = minBounds[i] + radius;
                    particle.oldPos[i] = particle.pos[i] + (particle.pos[i] - particle.oldPos[i]) * -restitution;
                }
                if (particle.pos[i] + radius > maxBounds[i]) {
                    particle.pos[i] = maxBounds[i] - radius;
                    particle.oldPos[i] = particle.pos[i] + (particle.pos[i] - particle.oldPos[i]) * -restitution;
                }
            }

            mesh.vertices[0] = particle.pos;
            mesh.updateVertices();
        }

        void render(const engine::graphics::Shader& shader) override {
            shader.setMat4("model", glm::translate(glm::mat4(1.0f), particle.pos));
            mesh.draw(GL_POINTS);
        }
    };

} // namespace engine::objects