#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine::graphics {

    // Abstracted movement directions
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    /**
     * @brief 3D camera system using Euler angles.
     *        Supports basic flycam behavior (FPS-style or orbital).
     */
    class Camera {
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        float Yaw;
        float Pitch;
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix(float aspectRatio) const;

        void ProcessKeyboard(CameraMovement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void ProcessMouseScroll(float yoffset);

    private:
        void updateCameraVectors();
    };

} // namespace engine::graphics
