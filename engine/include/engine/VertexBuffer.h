#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Engine {
    namespace Renderer {

        /**
         * The VertexBuffer class controls not only an actual GPU
         * vertex buffer but also an index buffer.
         */
        class VertexBuffer
        {
        public:
            explicit VertexBuffer();

            VertexBuffer(const VertexBuffer &) = delete;

            ~VertexBuffer();

            /**
             * drawTriangles() binds the vertex and index buffer and
             * draws their contents as triangles.
             */
            void drawTriangles();

            /**
             * Submit data contained in the std::vector to GPU memory.
             * @tparam T data type of objects contained in the vector.
             * @param vertices the vector containing the data to be submitted.
             */
            template<typename T>
            void setData(const std::vector<T> &vertices)
            {
                setRawData((const void *) vertices.data(), sizeof(T), vertices.size());
            }

            /**
             * Submit a vector of indices (unsigned int) to an index
             * buffer in GPU memory.
             * @param indices The vector of indices.
             */
            void setIndices(const std::vector<unsigned int> &indices);

            /**
             * Describe the layout of your vertices by calling this function.
             * @param count Number of floats the current attribute contains.
             */
            void addFloatLayoutAttribute(size_t count);

        private:
            void setRawData(const void *data, size_t size, size_t count);

            void bind();

            static void unbind();

        private:
            unsigned int m_indexCount;
            unsigned int m_attributeIndex;
            unsigned int m_vertexArray, m_vertexBuffer, m_indexBuffer;
        };
    } // Engine
} // Renderer
