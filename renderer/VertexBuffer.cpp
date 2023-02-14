//
// Created by alex on 2/14/23.
//

#include "VertexBuffer.h"

#include <GL/glew.h>

using namespace Engine::Renderer;

VertexBuffer::VertexBuffer()
{
    glGenVertexArrays(1, &m_vertexArrayId);
    glGenBuffers(1, &m_vertexBufferId);
    glGenBuffers(1, &m_indexBufferId);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_indexBufferId);
    glDeleteBuffers(1, &m_vertexBufferId);
    glDeleteVertexArrays(1, &m_vertexArrayId);
}

void VertexBuffer::bind()
{
    glBindVertexArray(m_vertexArrayId);
}
