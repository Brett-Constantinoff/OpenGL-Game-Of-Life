#ifndef PLAYGROUNDLAYER_H
#define PLAYGROUNDLAYER_H

#include "../../Core/Src/Core/Layer.h"
#include "../../Core/Src/Core/Application.h"
#include "../../Core/Src/OpenGL/OpenglBuild.h"
#include "../../Core/Src/ImGui/ImguiBuild.h"
#include "../../Core/Util/Shader.h"
#include "../../Core/Util/TextRenderer.h"
#include "../../Core/Util/Camera.h"
#include "../../Core/Util/VertexBuffer.h"
#include "../../Core/Util/VertexArray.h"

#include "../../Core/Libs/glm/glm.hpp"
#include "../../Core/Libs/glm/gtc/matrix_transform.hpp"
#include "../../Core/Libs/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <sstream>

#define CUBE_INDEX_COUNT 36

#define PLATFORM_CUBES 10000
#define GAME_OF_LIFE_CUBES 10000

#define MAX_CUBES 20000

class GameOfLifeLayer : public Layer{
    public:
        GameOfLifeLayer();
        virtual ~GameOfLifeLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate(float dt, Window* win) override;
        virtual void onRender() override; 
        virtual void onRenderImgui() override;

    private:
        Shader* m_shader;
        Shader* m_textShader;
        Camera* m_camera;
        TextRenderer* m_textRenderer;
        VertexArray* m_vao;
        VertexBuffer* m_vbo;
        VertexBuffer* m_transformBuffer;
        VertexBuffer* m_colourBuffer;

        glm::mat4* m_transforms;
        glm::vec3* m_colours;

        std::stringstream m_frameRate;
        std::stringstream m_camPosition;

        glm::mat4 m_projection;
        glm::mat4 m_view;

        uint32_t m_renderAmount = 0;

        
};  

#endif