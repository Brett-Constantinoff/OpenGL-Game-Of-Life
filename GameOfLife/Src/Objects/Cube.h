#ifndef CUBE_H
#define CUBE_H

#include "RenderObject.h"
#include <vector>
#include <iostream>
#include <limits>

#define CUBE_INDEX_COUNT 36
#define MAX_CUBES 20000

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
        uint32_t* getRenderAmount();

        void addInstance(glm::vec3 position);
        void removeInstance(glm::vec3 position);
        bool cubeExists(glm::vec3 position);
    
    private:
        std::vector<glm::mat4> m_transforms;
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_colours;
        VertexBuffer* m_colourVbo;
        VertexBuffer* m_transformBuffer;
        uint32_t m_renderAmount = 0;
        const glm::vec3 m_standardColour = {0.06f, 0.32f, 0.73f};
        const glm::vec3 m_selectionColour = {1.0f, 0.32f, 0.73f};
        const glm::vec3 m_gameOfLifeColour = {1.0f, 1.0f, 0.0f};
};


#endif