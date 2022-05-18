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

    private:
        Shader* m_shader;
        Shader* m_textShader;
        Camera* m_camera;
        TextRenderer* m_textRenderer;
        uint32_t m_vao;
        uint32_t m_vbo;
        uint32_t m_ibo;
        std::stringstream m_frameRate;

        glm::mat4 m_projection;
        glm::mat4 m_view;

        glm::vec3 m_quadColour;

        
};  

#endif