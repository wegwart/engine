#include <GL/glew.h>
#include <engine/VertexBuffer.h>

using namespace Engine::Renderer;

template<typename T>
VertexBuffer<T>::VertexBuffer()
        : m_indexCount(0)
{
    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_vertexBuffer);
    glGenBuffers(1, &m_indexBuffer);
}

template<typename T>
VertexBuffer<T>::~VertexBuffer()
{
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(1, &m_indexBuffer);
    glDeleteVertexArrays(1, &m_vertexArray);
}

template<typename T>
void VertexBuffer<T>::renderTriangles()
{
    bind();
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    unbind();
}

template<typename T>
void VertexBuffer<T>::bind()
{
    glBindVertexArray(m_vertexArray);
}

template<typename T>
void VertexBuffer<T>::unbind()
{
    glBindVertexArray(0);
}

template<typename T>
void VertexBuffer<T>::setData(const T *vertices, size_t count)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T) * count, vertices, GL_STATIC_DRAW);
}

template<typename T>
void VertexBuffer<T>::setIndices(const std::vector<unsigned int> &indices)
{
    m_indexCount = indices.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indexCount, indices.data(), GL_STATIC_DRAW);
}
