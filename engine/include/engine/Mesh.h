#pragma once

#include <string>
#include <engine/IndexBuffer.h>
#include <engine/VertexBuffer.h>

namespace Engine {
    class Mesh
    {
    public:
        Mesh() = default;

        ~Mesh() = default;

        void fromFile(const std::string &filename);

        void render();

    private:
        void clear();

    private:
        Renderer::IndexBuffer m_indexBuffer;
        Renderer::VertexBuffer m_vertexBuffer;
    };
}
