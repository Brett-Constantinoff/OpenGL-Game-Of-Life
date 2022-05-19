#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Buffer.h"
#include <stdint.h>

class VertexBuffer : public Buffer
{
    public:
        VertexBuffer(uint32_t type);
        virtual ~VertexBuffer();
        
        virtual void bind();
        virtual void setData(uint32_t byteSize, void* data, uint32_t mode);


};

#endif