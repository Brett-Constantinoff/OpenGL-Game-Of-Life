#ifndef BOARD_H
#define BOARD_H

#include "Objects/Cube.h"
#include "../../Core/Libs/glm/glm.hpp"
#include "../../Core/Libs/glm/gtc/matrix_transform.hpp"
#include "../../Core/Libs/glm/gtc/type_ptr.hpp"

class Board
{
    public:
        Board(int width, int height);
        ~Board();

        void print();
        void update(glm::vec3 position);
        void solve(Cube* cube);
        void reset();

    private:
        int getNeighbours(int index);

    private:
        int m_width;
        int m_height;
        int* m_board;
};

#endif