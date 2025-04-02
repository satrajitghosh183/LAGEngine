#include <SFML/Graphics.hpp>
#include "engine/scene/Scene.hpp"
#include "engine/scene/SceneManager.hpp"
#include "engine/objects/Ball2D.hpp"
#include "engine/objects/Cloth2D.hpp"

using namespace engine;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "2D Physics Scene");
    window.setFramerateLimit(60);

    scene::SceneManager sceneManager;
    auto* scene = sceneManager.get();

    // Spawn objects
    scene->add(new objects::Ball2D({400, 100}, {50, 0}, 10.0f));
    scene->add(new objects::Cloth2D(20, 10, 20.0f, {200, 50}));

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30));
        scene->update(dt);
        scene->render(window);
        window.display();
    }

    return 0;
}
