#ifndef PLAYGROUNDAPP_H
#define PLAYGROUNDAPP_H

#include "../../Core/Src/Core/Application.h"
#include "../../Core/Util/TextRenderer.h"
#include "GameOfLifeLayer.h"


class GameOfLife : public Application{
    public:
        GameOfLife(const std::string& label);
};

#endif