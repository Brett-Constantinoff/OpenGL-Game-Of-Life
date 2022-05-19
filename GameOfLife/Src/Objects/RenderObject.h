#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "../../../Core/Util/Shader.h"
#include "../../../Core/Libs/glm/glm.hpp"
#include "../../../Core/Util/VertexBuffer.h"
#include "../../../Core/Util/VertexArray.h"
#include "../../../Core/Libs/glm/gtc/matrix_transform.hpp"
#include "../../../Core/Libs/glm/gtc/type_ptr.hpp"
#include "../../../Core/Src/OpenGL/OpenglBuild.h"

class RenderObject{
    public:
        RenderObject();
        virtual ~RenderObject() = default;

        virtual void init(){};
        virtual void update(float dt){};
        virtual void render(){};
};

#endif