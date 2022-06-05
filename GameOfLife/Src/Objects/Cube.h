#ifndef CUBE_H
#define CUBE_H

#include "RenderObject.h"
#include <vector>
#include <iostream>
#include <limits>

#define CUBE_INDEX_COUNT 24
#define CUBE_VERTEX_COUNT 36
#define MAX_CUBES 20000
#define PLATFORM_CUBES 10000

class Cube : public RenderObject{
    public:
        Cube();
        virtual ~Cube();

        virtual void init() override;
        virtual void update(float dt) override;
        virtual void render() override;
        glm::mat4* getTransforms();
        glm::vec3* getColours();
        glm::vec3* getPositions();
        const glm::vec3* getStandarColour();
        const glm::vec3* getSelectionColour();
        glm::vec3* getGenerationColour();
        void setGenerationColour(glm::vec3 colour);
        int* getRenderAmount();
        void addInstance(glm::vec3 position);
        bool instanceExists(glm::vec3 position);
        void removeInstance(glm::vec3 position);
        void removeCells();


    private:
        void removePosition(int index);
        void removeColour(int index);
        void removeTransform(int index);

    private:
        std::vector<glm::mat4> m_transforms;
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_colours;
        VertexBuffer* m_colourVbo;
        VertexBuffer* m_transformBuffer;
        int m_renderAmount = 0;
        const glm::vec3 m_standardColour = {0.75f, 0.75f, 0.75f};
        const glm::vec3 m_selectionColour = {1.0f, 0.32f, 0.73f};
        glm::vec3 m_genColour;
};


#endif