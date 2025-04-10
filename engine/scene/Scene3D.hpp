// // #pragma once
// // #include <vector>
// // #include "Object3D.hpp"
// // #include "engine/graphics/Shader.hpp"

// // namespace engine::scene {

// //     class Scene3D {
// //     public:
// //         std::vector<Object3D*> objects;

// //         void add(Object3D* obj) {
// //             objects.push_back(obj);
// //         }

// //         void update(float dt) {
// //             for (auto* obj : objects)
// //                 if (obj && obj->visible)
// //                     obj->update(dt);
// //         }

// //         void render(const engine::graphics::Shader& shader) {
// //             for (auto* obj : objects)
// //                 if (obj && obj->visible)
// //                     obj->render(shader);
// //         }
// //     };

// // } // namespace engine::scene
// // engine/scene/Scene3D.hpp
// #pragma once
// #include <vector>
// #include "Object3D.hpp"
// #include "engine/graphics/Shader.hpp"
// #include "engine/physics/PhysicsWorld3D.hpp"

// namespace engine::scene {

//     class Scene3D {
//     public:
//         std::vector<Object3D*> objects;
//         physics::PhysicsWorld3D physicsWorld;

//         void add(Object3D* obj) {
//             objects.push_back(obj);
//         }

//         void update(float dt) {
//             // Physics step first
//             glm::vec3 gravity(0.0f, -980.0f, 0.0f);
//             physicsWorld.update(dt, gravity);

//             for (auto* obj : objects)
//                 if (obj && obj->visible)
//                     obj->update(dt);
//         }

//         void render(const engine::graphics::Shader& shader) {
//             for (auto* obj : objects)
//                 if (obj && obj->visible)
//                     obj->render(shader);
//         }
//     };

// } // namespace engine::scene
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Object3D.hpp"
#include "engine/graphics/Shader.hpp"
#include "engine/physics/PhysicsWorld3D.hpp"

namespace engine::scene {

    class Scene3D {
    public:
        std::vector<Object3D*> objects;
        physics::PhysicsWorld3D physicsWorld;

        void add(Object3D* obj) {
            objects.push_back(obj);
        }

        void update(float dt) {
            // ✅ Global physics simulation: handles all registered particles & tearing
            glm::vec3 gravity(0.0f, -980.0f, 0.0f);
            physicsWorld.update(dt, gravity);

            // Let scene objects run their own updates (like visual-only updates, etc.)
            for (auto* obj : objects)
                if (obj && obj->visible)
                    obj->update(dt);
        }

        void render(const engine::graphics::Shader& shader) {
            for (auto* obj : objects)
                if (obj && obj->visible)
                    obj->render(shader);
        }
    };

} // namespace engine::scene
