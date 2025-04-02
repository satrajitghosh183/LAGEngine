#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace engine::graphics {

    /**
     * @brief Represents a 3D mesh composed of vertices and optionally indices.
     *        Handles OpenGL VAO/VBO/EBO setup, updates, and draw calls.
     * 
     * This class is designed to support both:
     * - Procedural shapes (e.g., spheres, grids, cloth)
     * - Dynamic simulations (e.g., soft bodies, deformable surfaces)
     */
    class Mesh {
    public:
        // === Data containers ===
        std::vector<glm::vec3> vertices;         ///< Vertex positions
        std::vector<unsigned int> indices;       ///< Optional index buffer for triangles

        // === OpenGL handles ===
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;

        bool useIndices = false;                 ///< Tracks if we're using indexed rendering

        Mesh() = default;

        /**
         * @brief Uploads mesh data to the GPU.
         * 
         * @param dynamic If true, uses GL_DYNAMIC_DRAW for vertex updates.
         */
        void upload(bool dynamic = false) {
            if (VAO == 0) glGenVertexArrays(1, &VAO);
            if (VBO == 0) glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            // Vertex Buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
                         vertices.data(), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

            // Vertex layout: position only (location = 0)
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
            glEnableVertexAttribArray(0);

            // Index Buffer (optional)
            if (!indices.empty()) {
                if (EBO == 0) glGenBuffers(1, &EBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                             indices.data(), GL_STATIC_DRAW);
                useIndices = true;
            }

            glBindVertexArray(0);
        }

        /**
         * @brief Updates vertex buffer on the GPU.
         *        Only call this if your mesh is dynamic (e.g., cloth simulation).
         */
        void updateVertices() const {
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), vertices.data());
        }

        /**
         * @brief Draws the mesh using the bound shader.
         * 
         * @param mode GL_POINTS, GL_TRIANGLES, etc.
         */
        void draw(GLenum mode = GL_POINTS) const {
            glBindVertexArray(VAO);
            if (useIndices) {
                glDrawElements(mode, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
            } else {
                glDrawArrays(mode, 0, static_cast<GLsizei>(vertices.size()));
            }
            glBindVertexArray(0);
        }

        /**
         * @brief Frees GPU resources (optional cleanup).
         */
        void destroy() {
            if (VBO) glDeleteBuffers(1, &VBO);
            if (EBO) glDeleteBuffers(1, &EBO);
            if (VAO) glDeleteVertexArrays(1, &VAO);
            VBO = VAO = EBO = 0;
        }
    };

} // namespace engine::graphics
