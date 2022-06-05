#ifndef PLAYGROUNDLAYER_H
#define PLAYGROUNDLAYER_H

#include "../../Core/Src/Core/Layer.h"
#include "../../Core/Src/Core/Application.h"
#include "../../Core/Src/OpenGL/OpenglBuild.h"
#include "../../Core/Src/ImGui/ImguiBuild.h"
#include "../../Core/Util/Shader.h"
#include "../../Core/Util/TextRenderer.h"
#include "../../Core/Util/Camera.h"
#include "../../Core/Util/MousePicker.h"
#include "../../Core/Libs/glm/glm.hpp"
#include "../../Core/Libs/glm/gtc/matrix_transform.hpp"
#include "../../Core/Libs/glm/gtc/type_ptr.hpp"
#include "Objects/Cube.h"
#include "Board.h"
#include <iostream>
#include <sstream>

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

        virtual void onAttach(Window* win) override;
        virtual void onDetach() override;
        virtual void onUpdate(float dt) override;
        virtual void onRender() override; 
        virtual void onRenderImgui() override;

    private:
        void printBoard();

    private:
        Window* m_window;
        Shader* m_shader;
        Shader* m_textShader;
        Camera* m_camera;
        TextRenderer* m_textRenderer;
        MousePicker* m_mousePicker;
        Board* m_board;

        std::stringstream m_frameRate;
        std::stringstream m_spawnedObjects;
        std::stringstream m_generation;
        int m_currentGen = 0;

        glm::mat4 m_projection;
        glm::mat4 m_view;

        Cube* m_cube;
        int m_previousIntersection = 0;
        int m_currentIntersection = 0;

        float m_lastClick = 0.0f;
        float m_solveTime = 0.0f;

        State m_state;
};  

#endif