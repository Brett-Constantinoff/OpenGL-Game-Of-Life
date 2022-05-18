#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "../Core/Layer.h"
#include "ImguiBuild.h"


class ImguiLayer : public Layer{
    public:
        ImguiLayer(GLFWwindow* win);
        virtual ~ImguiLayer();

        void begin();
        void end();

        virtual void onAttach() override;
    private:
        GLFWwindow* m_win;
};


#endif