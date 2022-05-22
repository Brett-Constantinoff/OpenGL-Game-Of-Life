#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "../../../Core/Util/Shader.h"
#include "../../../Core/Libs/glm/glm.hpp"
#include "../../../Core/Util/VertexBuffer.h"
#include "../../../Core/Util/VertexArray.h"
#include "../../../Core/Libs/glm/gtc/matrix_transform.hpp"
#include "../../../Core/Libs/glm/gtc/type_ptr.hpp"
#include "../../../Core/Src/OpenGL/OpenglBuild.h"
#include <vector>

class RenderObject{
    public:
        RenderObject();
        virtual ~RenderObject() = default;

        virtual void init(){};
        virtual void update(float dt){};
        virtual void render(){};

        glm::vec3* getMin();
        glm::vec3* getMax();

    protected:
        void calculateMinMax(std::vector<float> vertexPositions, glm::vec3& min, glm::vec3& max, uint32_t offset);
    
    protected:
        VertexArray* m_vao;
        glm::vec3 m_min;
        glm::vec3 m_max;

    
};

#endif