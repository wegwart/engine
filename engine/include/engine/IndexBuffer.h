#pragma once

#include <vector>

namespace Engine {
    namespace Renderer {
        class VertexBuffer;

        class IndexBuffer
        {
            friend class VertexBuffer;

        public:
            explicit IndexBuffer();

            IndexBuffer(const IndexBuffer &) = delete;

            ~IndexBuffer();

            /**
             * Submit a vector of indices (unsigned int) to an index
             * buffer in GPU memory.
             * @param indices The vector of indices.
             */
            void setIndices(const std::vector<unsigned int> &indices);

            unsigned int indexCount() const;

        protected:
            void bind();

            static void unbind();

        private:
            unsigned int m_id, m_indexCount;
        };
    }
}
