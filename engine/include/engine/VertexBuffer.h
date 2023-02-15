#pragma once

namespace Engine {
    namespace Renderer {

        class VertexBuffer
        {
        public:
            VertexBuffer();

            ~VertexBuffer();

            void bind();

        private:
            unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;
        };
    } // Engine
} // Renderer