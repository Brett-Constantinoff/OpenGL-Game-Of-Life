#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind()
{
    glBindVertexArray(m_id);
}

void VertexArray::unBind()
{
    glBindVertexArray(0);
}

void VertexArray::setAttribPointer(uint32_t location, uint32_t byteSize, uint32_t type, bool normalized, uint32_t stride, void* start, bool instanced){
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, byteSize, type, normalized, stride, start);

    if(instanced){
        glVertexAttribDivisor(location, 1);
    }
}