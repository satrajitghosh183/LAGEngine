// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
// #include "Shader.hpp"
// #include "Camera3D.hpp"
// #include "Cloth3D.hpp"
// #include "Ball3D.hpp"
// #include <vector>
// #include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>

// // Window dimensions.
// const unsigned int SCR_WIDTH = 1280;
// const unsigned int SCR_HEIGHT = 720;

// // Timing.
// float deltaTime = 0.0f;
// float lastFrame = 0.0f;

// // Create a global camera instance.
// Camera3D camera(glm::vec3(0.0f, 50.0f, 150.0f),
//                 glm::vec3(0.0f, 1.0f, 0.0f),
//                 -90.0f, -20.0f);

// // Mouse callback to process mouse movement.
// void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//     static bool firstMouse = true;
//     static float lastX = SCR_WIDTH / 2.0f;
//     static float lastY = SCR_HEIGHT / 2.0f;
    
//     if (firstMouse) {
//         lastX = static_cast<float>(xpos);
//         lastY = static_cast<float>(ypos);
//         firstMouse = false;
//     }
    
//     float xoffset = static_cast<float>(xpos) - lastX;
//     float yoffset = lastY - static_cast<float>(ypos);  // Reversed since y-coordinates go from bottom to top.
//     lastX = static_cast<float>(xpos);
//     lastY = static_cast<float>(ypos);
    
//     camera.ProcessMouseMovement(xoffset, yoffset);
// }

// // Scroll callback to process zoom.
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//     camera.ProcessMouseScroll(static_cast<float>(yoffset));
// }

// // Process keyboard input.
// void processInput(GLFWwindow* window) {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
    
//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//         camera.ProcessKeyboard(FORWARD, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//         camera.ProcessKeyboard(BACKWARD, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//         camera.ProcessKeyboard(LEFT, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//         camera.ProcessKeyboard(RIGHT, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//         camera.ProcessKeyboard(UP, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//         camera.ProcessKeyboard(DOWN, deltaTime);
// }

// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

// int main() {
//     // Initialize GLFW.
//     if (!glfwInit()) {
//         std::cerr << "Failed to initialize GLFW!" << std::endl;
//         return -1;
//     }
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
//     // Create a window.
//     GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Cloth & Balls Simulation", nullptr, nullptr);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window!" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
    
//     // Initialize GLEW.
//     if (glewInit() != GLEW_OK) {
//         std::cerr << "Failed to initialize GLEW!" << std::endl;
//         return -1;
//     }
    
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
//     // Set mouse and scroll callbacks.
//     glfwSetCursorPosCallback(window, mouse_callback);
//     glfwSetScrollCallback(window, scroll_callback);
//     // Disable the cursor.
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
//     glEnable(GL_DEPTH_TEST);
    
//     // Build and compile shader.
//     Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    
//     // Create simulation objects.
//     int clothWidth = 30, clothHeight = 20;
//     float spacing = 2.0f;
//     // Center the cloth.
//     Cloth3D cloth(clothWidth, clothHeight, spacing, glm::vec3(-clothWidth * spacing * 0.5f, 50.0f, 0.0f));
    
//     // Create balls.
//     std::vector<Ball3D> balls;
//     int numBalls = 50;
//     for (int i = 0; i < numBalls; ++i) {
//         float x = -50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 100.0f));
//         float y = 10.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 40.0f));
//         float z = -50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 100.0f));
//         glm::vec3 pos(x, y, z);
//         float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.1415926f;
//         float speed = 10.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 30.0f));
//         glm::vec3 vel(std::cos(angle) * speed, std::sin(angle) * speed, std::cos(angle) * speed);
//         float radius = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));
//         balls.emplace_back(pos, vel, radius);
//     }
    
//     // Simulation parameters.
//     glm::vec3 gravity(0.0f, -9.81f, 0.0f);
//     glm::vec3 wind(5.0f, 0.0f, 0.0f);
    
//     // Main loop.
//     while (!glfwWindowShouldClose(window)) {
//         float currentFrame = static_cast<float>(glfwGetTime());
//         deltaTime = currentFrame - lastFrame;
//         lastFrame = currentFrame;
        
//         processInput(window);
//         glfwPollEvents();
        
//         // Update simulation.
//         cloth.update(deltaTime, gravity + wind, 20);
//         for (auto &ball : balls)
//             ball.update(deltaTime, gravity, glm::vec3(-100.0f, 0.0f, -100.0f), glm::vec3(100.0f, 100.0f, 100.0f));
        
//         // Collision: balls push cloth particles.
//         for (auto &ball : balls) {
//             for (auto &p : cloth.particles) {
//                 glm::vec3 diff = p.pos - ball.particle.pos;
//                 float dist = glm::length(diff);
//                 float minDist = ball.radius + 0.5f; // Assume cloth particle radius ~0.5.
//                 if (dist < minDist && dist > 0.001f) {
//                     float penetration = minDist - dist;
//                     glm::vec3 correction = glm::normalize(diff) * penetration;
//                     if (!p.locked)
//                         p.pos += correction;
//                 }
//             }
//         }
        
//         // Rendering.
//         glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
//         shader.use();
//         glm::mat4 projection = camera.GetProjectionMatrix(static_cast<float>(SCR_WIDTH) / SCR_HEIGHT);
//         glm::mat4 view = camera.GetViewMatrix();
//         shader.setMat4("projection", projection);
//         shader.setMat4("view", view);
//         glm::mat4 model = glm::mat4(1.0f);
//         shader.setMat4("model", model);
        
//         // Render cloth as points.
//         std::vector<glm::vec3> clothVertices;
//         for (const auto &p : cloth.particles)
//             clothVertices.push_back(p.pos);
//         unsigned int clothVAO, clothVBO;
//         glGenVertexArrays(1, &clothVAO);
//         glGenBuffers(1, &clothVBO);
//         glBindVertexArray(clothVAO);
//         glBindBuffer(GL_ARRAY_BUFFER, clothVBO);
//         glBufferData(GL_ARRAY_BUFFER, clothVertices.size() * sizeof(glm::vec3), clothVertices.data(), GL_DYNAMIC_DRAW);
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
//         glEnableVertexAttribArray(0);
//         glPointSize(4.0f);
//         glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(clothVertices.size()));
//         glDeleteBuffers(1, &clothVBO);
//         glDeleteVertexArrays(1, &clothVAO);
        
//         // Render balls as points.
//         std::vector<glm::vec3> ballVertices;
//         for (const auto &ball : balls)
//             ballVertices.push_back(ball.particle.pos);
//         unsigned int ballVAO, ballVBO;
//         glGenVertexArrays(1, &ballVAO);
//         glGenBuffers(1, &ballVBO);
//         glBindVertexArray(ballVAO);
//         glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
//         glBufferData(GL_ARRAY_BUFFER, ballVertices.size() * sizeof(glm::vec3), ballVertices.data(), GL_DYNAMIC_DRAW);
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
//         glEnableVertexAttribArray(0);
//         glPointSize(6.0f);
//         glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(ballVertices.size()));
//         glDeleteBuffers(1, &ballVBO);
//         glDeleteVertexArrays(1, &ballVAO);
        
//         glfwSwapBuffers(window);
//     }
    
//     glfwTerminate();
//     return 0;
// }


#include <SFML/Graphics.hpp>
#include "Cloth.hpp"
#include "Ball.hpp"
#include "math.hpp"
#include "number_generator.hpp"  // For RNG functionality.
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cloth Simulation with Bouncing Balls");
    window.setFramerateLimit(60);

    // Create the cloth.
    int gridWidth = 30;
    int gridHeight = 20;
    float spacing = 10.f;
    sf::Vector2f clothOrigin(100.f, 50.f);
    Cloth cloth(gridWidth, gridHeight, spacing, clothOrigin);

    // Create a number of bouncing balls.
    std::vector<Ball> balls;
    const int numBalls = 50; // Adjust for a "legendary" number.
    for (int i = 0; i < numBalls; ++i) {
        float x = RNG::RNGf::getRange(300.f, 750.f);
        float y = RNG::RNGf::getRange(300.f, 550.f);
        sf::Vector2f pos(x, y);
        float angle = RNG::RNGf::getRange(0.f, 2 * Math::PI);
        float speed = RNG::RNGf::getRange(50.f, 200.f);
        sf::Vector2f vel(std::cos(angle) * speed, std::sin(angle) * speed);
        float radius = RNG::RNGf::getRange(5.f, 15.f);
        balls.emplace_back(pos, vel, radius);
    }

    // Gravity.
    sf::Vector2f gravity(0.f, 500.f);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        float dt = clock.restart().asSeconds();

        // Update the cloth.
        cloth.update(dt, gravity, 20);

        // Update the balls.
        for (auto &ball : balls) {
            ball.update(dt, gravity, window);
        }

        // Handle collisions between balls and cloth particles.
        // Assuming cloth particles are drawn as circles of radius 3.
        float particleRadius = 3.f;
        for (auto &ball : balls) {
            for (auto &particle : cloth.particles) {
                sf::Vector2f diff = particle.pos - ball.particle.pos;
                float dist = Math::length(diff);
                float minDist = ball.radius + particleRadius;
                if (dist < minDist && dist > 0.f) {
                    float penetration = minDist - dist;
                    sf::Vector2f correction = Math::normalize(diff) * penetration;
                    if (!particle.locked) {
                        particle.pos += correction;
                    }
                    // Optionally, you can push the ball as well:
                    // ball.particle.pos -= correction;
                }
            }
        }

        window.clear(sf::Color::Black);
        cloth.draw(window);
        for (const auto &ball : balls) {
            ball.draw(window);
        }
        window.display();
    }

    return 0;
}
