#ifndef OPENGLLAYER_H
#define OPENGLLAYER_H

#include "../Core/Layer.h"
#include "OpenglBuild.h"

class OpenglLayer : public Layer
{
    public:
        OpenglLayer();
        ~OpenglLayer();

        virtual void onAttach(Window* win) override;
};

#endif