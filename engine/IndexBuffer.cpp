#include <GL/glew.h>
#include <engine/IndexBuffer.h>

using namespace Engine::Renderer;

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &m_id);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::setIndices(const std::vector<unsigned int> &indices)
{
    bind();
    m_indexCount = indices.size();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indexCount, indices.data(), GL_STATIC_DRAW);
    unbind();
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::indexCount() const
{
    return m_indexCount;
}
