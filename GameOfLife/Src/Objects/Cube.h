#ifndef CUBE_H
#define CUBE_H

#include "RenderObject.h"
#include <vector>
#include <iostream>

#define CUBE_INDEX_COUNT 36
#define MAX_CUBES 10000

class Cube : public RenderObject{
    public:
        Cube();
        virtual ~Cube();

        virtual void init() override;
        virtual void update(float dt) override;
        virtual void render() override;

        glm::mat4* getTransforms();
        glm::vec3* getColours();
    
    private:
        glm::mat4* m_transforms;
        glm::vec3* m_colours;
        VertexBuffer* m_colourVbo;
        VertexArray* m_vao;

};


#endif