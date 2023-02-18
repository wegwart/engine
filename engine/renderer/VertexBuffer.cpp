#include <GL/glew.h>
#include <engine/IndexBuffer.h>
#include <engine/VertexBuffer.h>

using namespace Engine::Renderer;

VertexBuffer::VertexBuffer()
        : m_attributeIndex(0)
{
    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_vertexBuffer);

    bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    unbind();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteVertexArrays(1, &m_vertexArray);
}

void VertexBuffer::drawTriangles()
{
    bind();
    assert(m_vertexCount > 0);
    assert(m_vertexCount % 3 == 0);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    unbind();
}

void VertexBuffer::drawTriangles(IndexBuffer &indexBuffer)
{
    bind();
    indexBuffer.bind();
    assert(indexBuffer.indexCount() > 0);
    assert(indexBuffer.indexCount() % 3 == 0);
    glDrawElements(GL_TRIANGLES, indexBuffer.indexCount(), GL_UNSIGNED_INT, nullptr);
    IndexBuffer::unbind();
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
    m_vertexCount = count;
    glBufferData(GL_ARRAY_BUFFER, size * count, data, GL_STATIC_DRAW);
    unbind();
}

void VertexBuffer::addFloatLayoutAttribute(size_t count)
{
    bind();
    glVertexAttribPointer(m_attributeIndex, count, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(m_attributeIndex++);
    unbind();
}
