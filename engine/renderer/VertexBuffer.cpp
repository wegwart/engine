#include <GL/glew.h>
#include <engine/VertexBuffer.h>

using namespace Engine::Renderer;

VertexBuffer::VertexBuffer()
        : m_indexCount(0)
{
    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_vertexBuffer);
    glGenBuffers(1, &m_indexBuffer);

    bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    unbind();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(1, &m_indexBuffer);
    glDeleteVertexArrays(1, &m_vertexArray);
}

void VertexBuffer::drawTriangles()
{
    bind();
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    unbind();
}

void VertexBuffer::bind()
{
    glBindVertexArray(m_vertexArray);
}

void VertexBuffer::unbind()
{
    glBindVertexArray(0);
}

void VertexBuffer::setRawData(const void *data, size_t size, size_t count)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size * count, data, GL_STATIC_DRAW);
    unbind();
}

void VertexBuffer::setIndices(const std::vector<unsigned int> &indices)
{
    bind();
    m_indexCount = indices.size();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indexCount, indices.data(), GL_STATIC_DRAW);
    unbind();
}

void VertexBuffer::addFloatLayoutAttribute(size_t count)
{
    bind();
    glVertexAttribPointer(m_attributeIndex, count, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(m_attributeIndex++);
    unbind();
}
