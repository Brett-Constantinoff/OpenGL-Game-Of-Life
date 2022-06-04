#include "Board.h"

Board::Board(int width, int height) : m_width{width}, m_height{height}
{
    m_board = new int[m_width * m_height]{0};
}

Board::~Board()
{
    delete[] m_board;
}

void Board::print()
{
	for(int i = 0; i < m_height; i++)
	{
		for(int j = 0; j < m_width ; j++)
		{
			int index = (i * m_width) + j;
			std::cout << m_board[index] << " ";
		}
		std::cout << '\n';
	}
}

void Board::update(glm::vec3 position)
{
    int index = (position.x * m_width) + position.z;

    switch(m_board[index])
    {
        case 0: 
            m_board[index] = 1;
            break;
        case 1:
            m_board[index] = 0;
            break;
    }
}

void Board::solve(Cube* cube)
{
    
}

int Board::getNeighbours(int index)
{
    int n = 0;
    //only contiune if the index is large enough
    if(index - m_width > 0)
    {   
        //top left
        if(m_board[index - m_width - 1] == 1)
        {
            n++;
        }
        //top middle
        if(m_board[index - m_width] == 1)
        {
            n++;
        }
        //top right
        if(m_board[index - m_width + 1] == 1)
        {
            n++;
        }
        
    }
    //only continue if index is small enough
    if(index + m_width < (m_width * m_height))
    {
        //bottom left
        if(m_board[index + m_width - 1] == 1)
        {
            n++;
        }
        //bottom middle
        if(m_board[index + m_width] == 1)
        {
            n++;
        }
        //bottom right
        if(m_board[index + m_width + 1] == 1)
        {
            n++;
        }
        
    }
    if(index - 1 > 0 && index + 1 < m_width * m_height)
    {
        //left 
        if(m_board[index - 1] == 1)
        {
            n++;
        }
         //right 
        if(m_board[index + 1] == 1)
        {
            n++;
        }
    }
    
    return n;
}
