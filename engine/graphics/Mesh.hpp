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
        void upload(bool dynamic = false);

        /**
         * @brief Updates vertex buffer on the GPU.
         *        Only call this if your mesh is dynamic (e.g., cloth simulation).
         */
        void updateVertices() const;

        /**
         * @brief Draws the mesh using the bound shader.
         * 
         * @param mode GL_POINTS, GL_TRIANGLES, etc.
         */
        void draw(GLenum mode = GL_POINTS) const;

        /**
         * @brief Frees GPU resources (optional cleanup).
         */
        void destroy();
    };

} // namespace engine::graphics
