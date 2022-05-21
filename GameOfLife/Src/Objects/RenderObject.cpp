#include "RenderObject.h"

RenderObject::RenderObject()
{
    
}

void RenderObject::calculateMinMax(std::vector<float> vertexPositions, glm::vec3& min, glm::vec3& max)
{
    float maxNum = -std::numeric_limits<float>::infinity();
    float minNum = std::numeric_limits<float>::infinity();

    glm::vec3 maxVertexPos{maxNum, maxNum, maxNum};
    glm::vec3 minVertexPos{minNum, minNum, minNum};

    for(uint32_t i = 0; i < vertexPositions.size() - 3; i += 3)
    {
        glm::vec3 currVertexPos{vertexPositions[i], vertexPositions[i + 1], vertexPositions[i + 2]};
        if(currVertexPos.x >= maxVertexPos.x && 
            currVertexPos.y >= maxVertexPos.y && 
            currVertexPos.z >= maxVertexPos.z)
        {
            maxVertexPos = currVertexPos;
        }
        if(currVertexPos.x <= minVertexPos.x && 
            currVertexPos.y <= minVertexPos.y && 
            currVertexPos.z <= minVertexPos.z)
        {
            minVertexPos = currVertexPos;
        }
    }

    min = minVertexPos;
    max = maxVertexPos;
}

glm::vec3* RenderObject::getMin()
{
    return &m_min;
}

glm::vec3* RenderObject::getMax()
{
    return &m_max;
}
