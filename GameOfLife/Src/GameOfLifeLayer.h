#ifndef PLAYGROUNDLAYER_H
#define PLAYGROUNDLAYER_H

#include "../../Core/Src/Core/Layer.h"
#include "../../Core/Src/Core/Application.h"
#include "../../Core/Src/OpenGL/OpenglBuild.h"
#include "../../Core/Src/ImGui/ImguiBuild.h"
#include "../../Core/Util/Shader.h"
#include "../../Core/Util/TextRenderer.h"
#include "../../Core/Util/Camera.h"
#include "../../Core/Libs/glm/glm.hpp"
#include "../../Core/Libs/glm/gtc/matrix_transform.hpp"
#include "../../Core/Libs/glm/gtc/type_ptr.hpp"
#include "Objects/Cube.h"
#include <iostream>
#include <sstream>

class GameOfLifeLayer : public Layer{
    public:
        GameOfLifeLayer();
        virtual ~GameOfLifeLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate(float dt, Window* win) override;
        virtual void onRender() override; 
        virtual void onRenderImgui() override;

        void getMouseRay(
            glm::vec2 mouseCoord,
            glm::vec2 screenDim, 
            glm::mat4 projection, 
            glm::mat4 view, 
            glm::vec3& rayOut, 
            glm::vec3& rayOrigin);

    private:
        Shader* m_shader;
        Shader* m_textShader;
        Camera* m_camera;
        TextRenderer* m_textRenderer;

        std::stringstream m_frameRate;
        std::stringstream m_camPosition;

        glm::mat4 m_projection;
        glm::mat4 m_view;

        Cube* m_cube;

        
};  

#endif