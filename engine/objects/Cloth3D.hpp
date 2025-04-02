
// engine/objects/Cloth3D.hpp
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "engine/physics/Particle3D.hpp"
#include "engine/physics/Constraint3D.hpp"
#include "engine/graphics/Mesh.hpp"
#include "engine/scene/Object3D.hpp"
#include "engine/graphics/Shader.hpp"

namespace engine::objects {

    class Cloth3D : public engine::scene::Object3D {
    public:
        std::vector<engine::physics::Particle3D> particles;
        std::vector<engine::physics::Constraint3D> constraints;
        engine::graphics::Mesh mesh;
        int width, height;
        float spacing;

        Cloth3D(int w, int h, float s, const glm::vec3& origin)
            : width(w), height(h), spacing(s) {
            for (int j = 0; j < height; ++j) {
                for (int i = 0; i < width; ++i) {
                    glm::vec3 pos = origin + glm::vec3(i * spacing, -j * spacing, 0.0f);
                    engine::physics::Particle3D p(pos);
                    if (j == 0) p.locked = true;
                    particles.push_back(p);
                }
            }

            for (int j = 0; j < height; ++j) {
                for (int i = 0; i < width; ++i) {
                    int index = j * width + i;
                    if (i < width - 1)
                        constraints.emplace_back(index, index + 1, spacing);
                    if (j < height - 1)
                        constraints.emplace_back(index, index + width, spacing);
                }
            }

            updateMesh();
            mesh.upload(true);
        }

        void update(float) override {}

        void update(float dt, const glm::vec3& acceleration, int iterations) {
            for (auto& p : particles)
                p.update(dt, acceleration);

            for (int i = 0; i < iterations; ++i)
                for (auto& c : constraints)
                    c.satisfy(particles);

            updateMesh();
            mesh.updateVertices();
        }

        void render(const engine::graphics::Shader& shader) override {
            shader.setMat4("model", glm::mat4(1.0f));
            mesh.draw(GL_POINTS);
        }

    private:
        void updateMesh() {
            mesh.vertices.clear();
            for (const auto& p : particles)
                mesh.vertices.push_back(p.pos);
        }
    };

} // namespace engine::objects
