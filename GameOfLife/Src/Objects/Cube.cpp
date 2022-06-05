#include "Cube.h"

Cube::Cube()
{
    init();
}

Cube::~Cube()
{
    delete m_vao;
    delete m_colourVbo;
    delete m_transformBuffer;
}

void Cube::init()
{
    //reserve initial capacity for all vectors
    m_transforms.reserve(MAX_CUBES);
    m_positions.reserve(MAX_CUBES);
    m_colours.reserve(MAX_CUBES);

    m_genColour = {1.0f, 0.84f, 0.0f};

    m_vao = new VertexArray();
    m_vao->bind();

    std::vector<float> vertexData = {
        //positions                 //normals
        //front face
        1.0f, 1.0f, 1.0f,           0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,           0.0f, 0.0f, 1.0f, 
        0.0f, 0.0f, 1.0f,           0.0f, 0.0f, 1.0f, 
        0.0f, 0.0f, 1.0f,           0.0f, 0.0f, 1.0f, 
        1.0f, 0.0f, 1.0f,           0.0f, 0.0f, 1.0f, 
        1.0f, 1.0f, 1.0f,           0.0f, 0.0f, 1.0f,
        //right face
        1.0f, 1.0f, 0.0f,           1.0f, 0.0f, 0.0f, 
        1.0f, 1.0f, 1.0f,           1.0f, 0.0f, 0.0f, 
        1.0f, 0.0f, 1.0f,           1.0f, 0.0f, 0.0f, 
        1.0f, 0.0f, 1.0f,           1.0f, 0.0f, 0.0f, 
        1.0f, 0.0f, 0.0f,           1.0f, 0.0f, 0.0f, 
        1.0f, 1.0f, 0.0f,           1.0f, 0.0f, 0.0f, 
        //left face
        0.0f, 1.0f, 1.0f,           -1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f,           -1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 1.0f,           -1.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 1.0f,           -1.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f,           -1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f,           -1.0f, 0.0f, 0.0f, 
        //back face
        1.0f, 0.0f, 0.0f,            0.0f, 0.0f, -1.0f,  
        0.0f, 0.0f, 0.0f,            0.0f, 0.0f, -1.0f, 
        0.0f, 1.0f, 0.0f,            0.0f, 0.0f, -1.0f,  
        0.0f, 1.0f, 0.0f,            0.0f, 0.0f, -1.0f,  
        1.0f, 1.0f, 0.0f,            0.0f, 0.0f, -1.0f,  
        1.0f, 0.0f, 0.0f,            0.0f, 0.0f, -1.0f,  
        //top face
        1.0f, 1.0f, 1.0f,            0.0f, 1.0f, 0.0f, 
        1.0f, 1.0f, 0.0f,            0.0f, 1.0f, 0.0f, 
        0.0f, 1.0f, 0.0f,            0.0f, 1.0f, 0.0f, 
        0.0f, 1.0f, 0.0f,            0.0f, 1.0f, 0.0f, 
        0.0f, 1.0f, 1.0f,            0.0f, 1.0f, 0.0f, 
        1.0f, 1.0f, 1.0f,            0.0f, 1.0f, 0.0f, 
        //bottom face
        0.0f, 0.0f, 1.0f,            0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,            0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,            0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,            0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,            0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,            0.0f, -1.0f, 0.0f,
    
    };  
   

    calculateMinMax(vertexData, m_min, m_max, 6);

    VertexBuffer positionVbo(GL_ARRAY_BUFFER);
    positionVbo.bind();
	positionVbo.setData(vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
    m_vao->setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);

    VertexBuffer normalVbo(GL_ARRAY_BUFFER);
    normalVbo.bind();
    normalVbo.setData(vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
    m_vao->setAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

	int width = 100;
	int height = 100;
	glm::vec3 transform{0.0f, 0.0f, 0.0f};
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
            m_positions.push_back(transform);
			glm::mat4 transformMat = glm::translate(glm::mat4(1.0f), transform);
			m_transforms.push_back(transformMat);
			m_colours.push_back(m_standardColour);
			transform.x += 1.0f;
            m_renderAmount++;
		}
		transform.x = 0.0f;
		transform.z += 1.0f;
	}

    m_colourVbo = new VertexBuffer(GL_ARRAY_BUFFER);
	m_colourVbo->bind();
	m_colourVbo->setData(sizeof(glm::vec3) * m_renderAmount, &m_colours[0], GL_DYNAMIC_DRAW);
	m_vao->setAttribPointer(2, 3 , GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0, true);

    m_transformBuffer = new VertexBuffer(GL_ARRAY_BUFFER);
	m_transformBuffer->bind();
	m_transformBuffer->setData(sizeof(glm::mat4) * m_renderAmount, &m_transforms[0], GL_DYNAMIC_DRAW);

	m_vao->setAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0, true);
	m_vao->setAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)sizeof(glm::vec4), true);
	m_vao->setAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)), true);
	m_vao->setAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)), true);

	m_vao->unBind();

}

void Cube::update(float dt)
{

}

void Cube::render()
{
    m_vao->bind();
    m_colourVbo->bind();
    m_colourVbo->setData(sizeof(glm::vec3) * m_renderAmount, &m_colours[0], GL_DYNAMIC_DRAW);

    m_transformBuffer->bind();
	m_transformBuffer->setData(sizeof(glm::mat4) * m_renderAmount, &m_transforms[0], GL_DYNAMIC_DRAW);

    glDrawArraysInstanced(GL_TRIANGLES, 0, CUBE_VERTEX_COUNT, m_renderAmount);
	m_vao->unBind();
}

glm::mat4* Cube::getTransforms()
{
    return &m_transforms[0];
}

glm::vec3* Cube::getColours()
{
    return &m_colours[0];
}

glm::vec3* Cube::getPositions()
{
    return &m_positions[0];
}

const glm::vec3* Cube::getStandarColour()
{
    return &m_standardColour;
}

const glm::vec3* Cube::getSelectionColour()
{
    return &m_selectionColour;
}

glm::vec3* Cube::getGenerationColour()
{
    return &m_genColour;
}

void Cube::setGenerationColour(glm::vec3 colour)
{
    m_genColour = colour;
}

int* Cube::getRenderAmount()
{
    return &m_renderAmount;
}

void Cube::addInstance(glm::vec3 position)
{
    if(m_renderAmount < MAX_CUBES)
    {
        m_positions.push_back(position);
        m_colours.push_back(m_genColour);
        m_transforms.push_back(glm::translate(glm::mat4(1.0f), position));
        m_renderAmount++;
    }
}

bool Cube::instanceExists(glm::vec3 position)
{
    return std::find(m_positions.begin(), m_positions.end(), position) != m_positions.end();
}

void Cube::removeInstance(glm::vec3 position)
{
    int index = std::find(m_positions.begin(), m_positions.end(), position) - m_positions.begin();
    m_positions.erase(m_positions.begin() + index);
    m_colours.erase(m_colours.begin() + index);
    m_transforms.erase(m_transforms.begin() + index);
    m_renderAmount--;
}

void Cube::removeCells()
{
    for(int i = m_renderAmount; i > PLATFORM_CUBES; i--)
    {
        m_positions.erase(m_positions.begin() + i - 1);
        m_colours.erase(m_colours.begin() + i - 1);
        m_transforms.erase(m_transforms.begin() + i - 1);
        m_renderAmount--;
    }
}








