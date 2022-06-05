#ifndef APPLICATION_H
#define APPLICATION_H

#include <string.h>
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "../OpenGL/OpenglLayer.h"
#include "../ImGui/ImguiLayer.h"


class Application
{
    public:
        Application(const std::string& label = "Application", uint32_t width = 1080, uint32_t height = 720);
        virtual ~Application() = 0;

        void start();
        void pushLayer(Layer* layer);

    private:
        OpenglLayer* m_openglLayer;
        ImguiLayer* m_imguiLayer;
        Window* m_window;   
        LayerStack* m_layerStack;
        float m_lastFrame = 0.0f;
};

#endif