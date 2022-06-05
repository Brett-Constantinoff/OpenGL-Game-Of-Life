#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "../Core/Layer.h"
#include "ImguiBuild.h"


class ImguiLayer : public Layer
{
    public:
        ImguiLayer();
        virtual ~ImguiLayer();

        void begin();
        void end();

        virtual void onAttach(Window* win) override;
};

#endif