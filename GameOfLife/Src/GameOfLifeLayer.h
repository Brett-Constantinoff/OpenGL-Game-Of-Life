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

#define CLICK_SPEED 0.15f

enum class State
{
    DEFAULT = 0,
    RUNNING = 1,
    RESET = 2,
};

class GameOfLifeLayer : public Layer
{
    public:
        GameOfLifeLayer();
        virtual ~GameOfLifeLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate(float dt, Window* win) override;
        virtual void onRender() override; 
        virtual void onRenderImgui() override;

        void getMouseRay(Window* win, glm::mat4 projection, glm::mat4 view, glm::vec3& ray, glm::vec3& rayOrigin);
        bool rayIntersect(glm::vec3 rayDir, glm::vec3 rayOrigin, glm::mat4 transform, glm::vec3 min, glm::vec3 max);
        bool perpPlaneIntersect(glm::vec3 axis, glm::vec3 delta, glm::vec3 rayDir, glm::vec3 min, glm::vec3 max, float& tMin, float& tMax);

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
        uint32_t m_previousIntersection = 0;
        uint32_t m_currentIntersection = 0;

        float m_lastClick = 0.0f;

        State m_state;
};  

#endif