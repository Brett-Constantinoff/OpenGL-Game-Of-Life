#include "GameOfLife.h"

int main(){
    GameOfLife* gameOfLife = new GameOfLife("Game Of Life");
    gameOfLife->start();
    delete gameOfLife;
    return 0;
}