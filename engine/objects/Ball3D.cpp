// #include "engine/objects/Ball3D.hpp"
// #include <glm/gtc/matrix_transform.hpp>

// namespace engine::objects {

//     Ball3D::Ball3D(const glm::vec3& pos, const glm::vec3& velocity, float r, float rest)
//         : particle(pos, velocity), radius(r), restitution(rest) {
//         mesh.vertices.push_back(pos); // Can replace with Sphere mesh later
//         mesh.upload();
//     }

//     void Ball3D::update(float) {}

//     void Ball3D::update(float dt, const glm::vec3& acceleration,
//                         const glm::vec3& minBounds, const glm::vec3& maxBounds) {
//         particle.update(dt, acceleration);

//         for (int i = 0; i < 3; ++i) {
//             if (particle.pos[i] - radius < minBounds[i]) {
//                 particle.pos[i] = minBounds[i] + radius;
//                 particle.oldPos[i] = particle.pos[i] + (particle.pos[i] - particle.oldPos[i]) * -restitution;
//             }
//             if (particle.pos[i] + radius > maxBounds[i]) {
//                 particle.pos[i] = maxBounds[i] - radius;
//                 particle.oldPos[i] = particle.pos[i] + (particle.pos[i] - particle.oldPos[i]) * -restitution;
//             }
//         }

//         mesh.vertices[0] = particle.pos;
//         mesh.updateVertices();
//     }

//     void Ball3D::render(const engine::graphics::Shader& shader) {
//         shader.setMat4("model", glm::translate(glm::mat4(1.0f), particle.pos));
//         mesh.draw(GL_POINTS);
//     }

// } // namespace engine::objects


#include "engine/objects/Ball3D.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace engine::objects {

    Ball3D::Ball3D(const glm::vec3& pos, const glm::vec3& velocity, float r, float rest)
        : particle(pos, velocity), radius(r), restitution(rest) {
        mesh.vertices.push_back(pos);
        mesh.upload();
    }

    void Ball3D::update(float) {}

    void Ball3D::update(float dt, const glm::vec3& acceleration,
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

    void Ball3D::render(const engine::graphics::Shader& shader) {
        shader.setMat4("model", glm::translate(glm::mat4(1.0f), particle.pos));
        mesh.draw(GL_POINTS);
    }

    void Ball3D::interactWithCloth(Cloth3D* cloth, float forceMultiplier) {
        for (auto& p : cloth->particles) {
            float dist = glm::length(p.pos - particle.pos);
            if (dist < radius) {
                glm::vec3 dir = glm::normalize(p.pos - particle.pos + glm::vec3(1e-4f));
                p.pos += dir * forceMultiplier; // Displace to simulate impulse
            }
        }
    }

}
