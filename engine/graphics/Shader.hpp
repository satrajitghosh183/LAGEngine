#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace engine::graphics {

    /**
     * @brief Wrapper class for OpenGL shader programs.
     *        Loads vertex + fragment shaders from file, compiles and links.
     */
    class Shader {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);

        // Activates the shader program
        void use() const;

        // Utility uniform functions
        void setMat4(const std::string& name, const glm::mat4& mat) const;
        void setVec3(const std::string& name, const glm::vec3& vec) const;
        void setFloat(const std::string& name, float value) const;
    };

} // namespace engine::graphics
