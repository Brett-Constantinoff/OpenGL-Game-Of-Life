#ifndef LAYER_H
#define LAYER_H

#include <string>
#include "Window.h"

class Layer{
    public: 
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void onAttach() {};
        virtual void onDetach() {};
        virtual void onUpdate(float dt, Window* win) {};
        virtual void onRender() {};
        virtual void onRenderImgui() {};

    protected:
        std::string m_name;

};

#endif