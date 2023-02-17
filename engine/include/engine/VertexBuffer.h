#pragma once

#include <vector>
#include <glm/glm.hpp>

static_assert(sizeof(glm::vec3) == 3 * sizeof(float));

namespace Engine {
    namespace Renderer {

        /**
         * The VertexBuffer class controls not only an actual GPU vertex buffer but
         * also an index buffer.
         * @tparam T
         */
        template<typename T>
        class VertexBuffer
        {
        public:
            explicit VertexBuffer();

            VertexBuffer(const VertexBuffer &) = delete;

            ~VertexBuffer();

            void renderTriangles();

            void setData(const T *vertices, size_t count);

            void setIndices(const std::vector<unsigned int> &indices);

        protected:
            void addLayoutAttribute(size_t size, ...);

        private:
            void bind();

            static void unbind();

        private:
            unsigned int m_indexCount;
            unsigned int m_vertexArray, m_vertexBuffer, m_indexBuffer;
        };


        struct MeshVertex
        {
            glm::vec3 position;
            glm::vec3 normals;
            glm::vec3 textureCoords;
            // ...
        };

        class MeshVertexBuffer : public VertexBuffer<MeshVertex>
        {
        public:
            MeshVertexBuffer() = default;

            ~MeshVertexBuffer() = default;
        };
    } // Engine
} // Renderer
