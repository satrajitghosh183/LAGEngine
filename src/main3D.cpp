#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/graphics/Shader.hpp"
#include "engine/graphics/Camera.hpp"
#include "engine/scene/Scene.hpp"
#include "engine/scene/SceneManager.hpp"
#include "engine/objects/Ball3D.hpp"
#include "engine/objects/Cloth3D.hpp"

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
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);

    graphics::Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    scene::SceneManager sceneManager;
    auto* scene = sceneManager.get();

    scene->add(new objects::Ball3D({0, 50, 0}, {10, 0, 0}, 5.0f));
    scene->add(new objects::Cloth3D(20, 10, 2.0f, {-20, 40, 0}));

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

        scene->update(deltaTime);
        scene->render(shader);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
