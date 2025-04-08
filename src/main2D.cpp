#include <SFML/Graphics.hpp>
#include "engine/scene/SceneManager.hpp"
#include "engine/objects/Ball2D.hpp"
#include "engine/objects/Cloth2D.hpp"

using namespace engine;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "2D Physics Scene");
    window.setFramerateLimit(60);

    scene::SceneManager sceneManager;
    scene::Scene* scene = sceneManager.get();

    // Add 2D objects
    auto ball = new objects::Ball2D({400, 100}, {50, 0}, 10.0f);
    auto cloth = new objects::Cloth2D(20, 10, 20.0f, {200, 50});
    scene->add(ball);
    scene->add(cloth);

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sceneManager.update(dt);

        window.clear(sf::Color(30, 30, 30));
        sceneManager.render(window);
        window.display();
    }

    return 0;
}
