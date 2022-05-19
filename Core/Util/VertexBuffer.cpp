#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(uint32_t type) : Buffer(type)
{
    glGenBuffers(1, &m_id);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind()
{
    glBindBuffer(m_type, m_id);
}

void VertexBuffer::setData(uint32_t byteSize, void* data, uint32_t mode)
{
    glBufferData(m_type, byteSize, data, mode);
}

