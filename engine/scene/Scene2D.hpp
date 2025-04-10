// #pragma once
// #include <vector>
// #include "Object2D.hpp"
// #include <SFML/Graphics.hpp>

// namespace engine::scene {

//     class Scene2D {
//     public:
//         std::vector<Object2D*> objects;

//         void add(Object2D* obj) {
//             objects.push_back(obj);
//         }

//         void update(float dt) {
//             for (auto* obj : objects)
//                 if (obj && obj->active)
//                     obj->update(dt);
//         }

//         void render(sf::RenderWindow& window) {
//             for (auto* obj : objects)
//                 if (obj && obj->active)
//                     obj->render(window);
//         }
//     };

// } // namespace engine::scene
#pragma once
#include <vector>
#include "Object2D.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace engine::scene {

    class Scene2D {
    public:
        std::vector<Object2D*> objects;

        void add(Object2D* obj) {
            objects.push_back(obj);
        }

        void update(float dt) {
            for (auto* obj : objects)
                if (obj && obj->visible)
                    obj->update(dt);
        }

        void render(sf::RenderWindow& window) {
            for (auto* obj : objects)
                if (obj && obj->visible)
                    obj->render(window);
        }
    };
}
