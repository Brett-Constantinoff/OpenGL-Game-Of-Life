#include "GameOfLife.h"

GameOfLife::GameOfLife(const std::string &label) : Application(label){
    pushLayer(new GameOfLifeLayer());
}
