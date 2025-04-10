// // // engine/objects/Cloth3D.cpp
// // #include "engine/objects/Cloth3D.hpp"
// // #include <glm/gtc/matrix_transform.hpp>

// // namespace engine::objects {

// //     Cloth3D::Cloth3D(int w, int h, float s, const glm::vec3& origin)
// //         : width(w), height(h), spacing(s) {
// //         for (int j = 0; j < height; ++j) {
// //             for (int i = 0; i < width; ++i) {
// //                 glm::vec3 pos = origin + glm::vec3(i * spacing, -j * spacing, 0.0f);
// //                 engine::physics::Particle3D p(pos);
// //                 if (j == 0) p.locked = true;
// //                 particles.push_back(p);
// //             }
// //         }

// //         for (int j = 0; j < height; ++j) {
// //             for (int i = 0; i < width; ++i) {
// //                 int index = j * width + i;
// //                 if (i < width - 1)
// //                     constraints.emplace_back(index, index + 1, spacing);
// //                 if (j < height - 1)
// //                     constraints.emplace_back(index, index + width, spacing);
// //             }
// //         }

// //         updateMesh();
// //         mesh.upload(true);
// //     }

// //     void Cloth3D::update(float) {}

// //     void Cloth3D::update(float dt, const glm::vec3& acceleration, int iterations) {
// //         for (auto& p : particles)
// //             p.update(dt, acceleration);

// //         for (int i = 0; i < iterations; ++i)
// //             for (auto& c : constraints)
// //                 c.satisfy(particles);

// //         updateMesh();
// //         mesh.updateVertices();
// //     }

// //     void Cloth3D::render(const engine::graphics::Shader& shader) {
// //         shader.setMat4("model", glm::mat4(1.0f));
// //         mesh.draw(GL_POINTS);
// //     }

// //     void Cloth3D::updateMesh() {
// //         mesh.vertices.clear();
// //         for (const auto& p : particles)
// //             mesh.vertices.push_back(p.pos);
// //     }

// // } // namespace engine::objects
// #include "engine/objects/Cloth3D.hpp"
// #include "engine/scene/SceneManager.hpp"
// #include <glm/gtc/matrix_transform.hpp>

// namespace engine::objects {

//     Cloth3D::Cloth3D(int w, int h, float s, const glm::vec3& origin)
//         : width(w), height(h), spacing(s) {
//         using namespace engine::scene;

//         for (int j = 0; j < height; ++j) {
//             for (int i = 0; i < width; ++i) {
//                 glm::vec3 pos = origin + glm::vec3(i * spacing, -j * spacing, 0.0f);
//                 engine::physics::Particle3D p(pos);
//                 if (j == 0) p.locked = true;
//                 particles.push_back(p);
//             }
//         }

//         for (int j = 0; j < height; ++j) {
//             for (int i = 0; i < width; ++i) {
//                 int index = j * width + i;
//                 if (i < width - 1)
//                     constraints.emplace_back(index, index + 1, spacing);
//                 if (j < height - 1)
//                     constraints.emplace_back(index, index + width, spacing);
//             }
//         }

//         // ✅ Register particles and constraints to physicsWorld
//         auto* world = &SceneManager::get3D()->physicsWorld;
//         for (auto& p : particles) world->addParticle(&p);
//         for (auto& c : constraints) world->addConstraint(&c);

//         updateMesh();
//         mesh.upload(true);
//     }

//     void Cloth3D::update(float) {}

//     void Cloth3D::update(float dt, const glm::vec3& acceleration, int iterations) {
//         for (auto& p : particles)
//             p.update(dt, acceleration);

//         for (int i = 0; i < iterations; ++i)
//             for (auto& c : constraints)
//                 c.satisfy(particles);

//         updateMesh();
//         mesh.updateVertices();
//     }

//     void Cloth3D::render(const engine::graphics::Shader& shader) {
//         shader.setMat4("model", glm::mat4(1.0f));
//         mesh.draw(GL_POINTS);
//     }

//     void Cloth3D::updateMesh() {
//         mesh.vertices.clear();
//         for (const auto& p : particles)
//             mesh.vertices.push_back(p.pos);
//     }

// } // namespace engine::objects
// engine/objects/Cloth3D.cpp
#include "engine/objects/Cloth3D.hpp"
#include "engine/scene/SceneManager3D.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace engine::objects {
    Cloth3D::Cloth3D(int w, int h, float s, const glm::vec3& origin, engine::scene::SceneManager3D& sceneManager)
    : width(w), height(h), spacing(s), sceneManagerRef(sceneManager) {

        class SceneManager3D;
        using namespace engine::scene;

        // Create particles
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                glm::vec3 pos = origin + glm::vec3(i * spacing, -j * spacing, 0.0f);
                engine::physics::Particle3D p(pos);
                if (j == 0) p.locked = true;
                particles.push_back(p);
            }
        }

        // Create structural constraints
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                int index = j * width + i;
                if (i < width - 1)
                    constraints.emplace_back(index, index + 1, spacing);
                if (j < height - 1)
                    constraints.emplace_back(index, index + width, spacing);
            }
        }

        // Register into physics world
        engine::physics::PhysicsWorld3D* world = &sceneManagerRef.get()->physicsWorld;

        for (auto& p : particles) world->addParticle(&p);
        for (auto& c : constraints) world->addConstraint(&c);

        updateMesh();
        mesh.upload(true);
    }

    void Cloth3D::update(float) {
        // No-op: updated by PhysicsWorld3D
    }

    void Cloth3D::update(float dt, const glm::vec3& acceleration, int iterations) {
        for (auto& p : particles)
            p.update(dt, acceleration);

        for (int i = 0; i < iterations; ++i)
            for (auto& c : constraints)
                c.satisfy(particles);

        updateMesh();
        mesh.updateVertices();
        mesh.updateNormals();
    }

    void Cloth3D::render(const engine::graphics::Shader& shader) {
        shader.setMat4("model", glm::mat4(1.0f));
        mesh.draw(GL_TRIANGLES);
    }

    void Cloth3D::updateMesh() {
        mesh.vertices.clear();
        mesh.normals.clear();
        mesh.indices.clear();

        // Push vertex positions
        for (const auto& p : particles)
            mesh.vertices.push_back(p.pos);

        // Build triangle indices
        for (int j = 0; j < height - 1; ++j) {
            for (int i = 0; i < width - 1; ++i) {
                int i0 = j * width + i;
                int i1 = j * width + i + 1;
                int i2 = (j + 1) * width + i;
                int i3 = (j + 1) * width + i + 1;

                mesh.indices.push_back(i0);
                mesh.indices.push_back(i2);
                mesh.indices.push_back(i1);

                mesh.indices.push_back(i1);
                mesh.indices.push_back(i2);
                mesh.indices.push_back(i3);
            }
        }

        // Recalculate normals
        mesh.normals.resize(mesh.vertices.size(), glm::vec3(0.0f));
        for (size_t i = 0; i < mesh.indices.size(); i += 3) {
            int i0 = mesh.indices[i];
            int i1 = mesh.indices[i + 1];
            int i2 = mesh.indices[i + 2];

            const glm::vec3& v0 = mesh.vertices[i0];
            const glm::vec3& v1 = mesh.vertices[i1];
            const glm::vec3& v2 = mesh.vertices[i2];

            glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
            mesh.normals[i0] += normal;
            mesh.normals[i1] += normal;
            mesh.normals[i2] += normal;
        }

        for (auto& n : mesh.normals)
            n = glm::normalize(n);
    }

} // namespace engine::objects
