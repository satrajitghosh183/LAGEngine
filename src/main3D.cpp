// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include "engine/graphics/Shader.hpp"
// #include "engine/graphics/Camera.hpp"
// #include "engine/scene/SceneManager.hpp"
// #include "engine/objects/Ball3D.hpp"
// #include "engine/objects/Cloth3D.hpp"
// #include <iostream>
// #include <vector>
// #include <cmath>

// using namespace engine;

// const unsigned int WIDTH = 1280;
// const unsigned int HEIGHT = 720;
// graphics::Camera camera({0, 50, 150}, {0, 1, 0}, -90.f, -20.f);

// int main() {
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3D Physics Scene", nullptr, nullptr);
//     if (!window) {
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);

//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

//     glEnable(GL_DEPTH_TEST);

//     graphics::Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

//     scene::SceneManager sceneManager;
//     scene::Scene3D* scene = sceneManager.get3D();  // ✅ Use 3D scene

//     auto ball = new objects::Ball3D({0, 50, 0}, {10, 0, 0}, 5.0f);
//     auto cloth = new objects::Cloth3D(20, 10, 2.0f, {-20, 40, 0});
//     scene->add(ball);
//     scene->add(cloth);

//     float lastFrame = 0.0f;
//     while (!glfwWindowShouldClose(window)) {
//         float currentFrame = glfwGetTime();
//         float deltaTime = currentFrame - lastFrame;
//         lastFrame = currentFrame;

//         glfwPollEvents();

//         glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         shader.use();
//         shader.setMat4("view", camera.GetViewMatrix());
//         shader.setMat4("projection", camera.GetProjectionMatrix((float)WIDTH / HEIGHT));

//         sceneManager.update3D(deltaTime);         // ✅ Updated method
//         sceneManager.render3D(shader);            // ✅ Updated method

//         glfwSwapBuffers(window);
//     }

//     glfwTerminate();
//     return 0;
// }
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/graphics/Shader.hpp"
#include "engine/graphics/Camera.hpp"
#include "engine/scene/SceneManager3D.hpp"  // ✅ Use 3D-specific header
#include "engine/objects/Ball3D.hpp"
#include "engine/objects/Cloth3D.hpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace engine;

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;
graphics::Camera camera({0, 50, 150}, {0, 1, 0}, -90.f, -20.f);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3D Physics Scene", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    graphics::Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    scene::SceneManager3D sceneManager;  // ✅ Correct manager class
    scene::Scene3D* scene = sceneManager.get();   // ✅ get() not get3D()

    auto ball = new objects::Ball3D({0, 50, 0}, {10, 0, 0}, 5.0f);
    auto cloth = new objects::Cloth3D(20, 10, 2.0f, {-20, 40, 0}, sceneManager);
    scene->add(ball);
    scene->add(cloth);

    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setMat4("view", camera.GetViewMatrix());
        shader.setMat4("projection", camera.GetProjectionMatrix((float)WIDTH / HEIGHT));

        sceneManager.update(deltaTime);         // ✅ 3D-specific update
        sceneManager.render(shader);            // ✅ 3D-specific render

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
