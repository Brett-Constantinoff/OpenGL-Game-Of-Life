#ifndef BUFFER_H
#define BUFFER_H

#include "../Src/OpenGL/OpenglBuild.h"
#include <stdint.h>

class Buffer
{
    public:
        Buffer(uint32_t type);
        virtual ~Buffer(){};
        
        virtual void bind(){};
        virtual void setData(uint32_t byteSize, void* data, uint32_t mode){};
    
    protected:
        uint32_t m_type;
        uint32_t m_id;
};

#endif