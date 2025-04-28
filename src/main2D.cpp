#include <SFML/Graphics.hpp>
#include "engine/scene/SceneManager2D.hpp"
#include "engine/objects/Ball2D.hpp"
#include "engine/objects/Cloth2D.hpp"
#include "engine/objects/Cannon2D.hpp"
#include <vector>

using namespace engine;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "2D Physics Scene");
    window.setFramerateLimit(60);

    scene::SceneManager2D sceneManager;
    scene::Scene2D* scene = sceneManager.get2D();

    std::vector<objects::Ball2D*> projectiles; 

    auto cloth = new objects::Cloth2D(20, 10, 20.0f, {200, 50});
    auto cannon = new objects::Cannon2D({300, 700});

    cloth->setProjectiles(&projectiles); 

    scene->add(cloth);
    scene->add(cannon);

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left)
                    cannon->rotate(-5.f);
                if (event.key.code == sf::Keyboard::Right)
                    cannon->rotate(5.f);
                if (event.key.code == sf::Keyboard::Space) {
                    auto velocity = cannon->getFiringVelocity();
                    auto ball = new objects::Ball2D(cannon->position, velocity, 10.0f);
                    scene->add(ball);
                    projectiles.push_back(ball); 
                }
            }
        }

        sceneManager.update2D(dt);
        window.clear(sf::Color(30, 30, 30));
        sceneManager.render2D(window);
        window.display();
    }

    return 0;
}
