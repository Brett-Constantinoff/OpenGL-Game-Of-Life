#include "Cube.h"

Cube::Cube()
{
    init();
}

Cube::~Cube()
{
    delete[] m_transforms;
    delete[] m_colours;
    delete m_vao;
    delete m_colourVbo;
}

void Cube::init()
{
    m_vao = new VertexArray();
    m_vao->bind();

    std::vector<float> vertexData = {
       //positions         
       0.0f, 0.0f, 0.0f,   
       1.0f, 0.0f, 0.0f,   
       1.0f, 1.0f, 0.0f,   
       0.0f, 1.0f, 0.0f,   

       1.0f, 0.0f, 0.0f,    
       1.0f, 0.0f, 1.0f,   
       1.0f, 1.0f, 1.0f,   
       1.0f, 1.0f, 0.0f,   

       0.0f, 0.0f, 1.0f,   
       0.0f, 1.0f, 1.0f,   
       1.0f, 1.0f, 1.0f,   
       1.0f, 0.0f, 1.0f,   

       0.0f, 0.0f, 0.0f,   
       0.0f, 1.0f, 0.0f,   
       0.0f, 1.0f, 1.0f,   
       0.0f, 0.0f, 1.0f,   

       0.0f, 1.0f, 0.0f,   
       1.0f, 1.0f, 0.0f,    
       0.0f, 1.0f, 1.0f,    
       1.0f, 1.0f, 1.0f,   

       0.0f, 0.0f, 1.0f,    
       0.0f, 1.0f, 1.0f,    
       1.0f, 1.0f, 1.0f,    
       1.0f, 0.0f, 1.0f,    
    };


    calculateMinMax(vertexData, m_min, m_max);

    VertexBuffer vbo(GL_ARRAY_BUFFER);
    vbo.bind();
	vbo.setData(vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
    m_vao->setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    std::vector<uint32_t> indices = {
        0,  1,  2,      0,  2,  3,
        4,  5,  6,      4,  6,  7,   
        8,  9,  10,     8,  10, 11,  
        12, 13, 14,     12, 14, 15, 
        16, 17, 18,     17, 18, 19,  
        20, 21, 22,     21, 22, 23
    };

    VertexBuffer ibo(GL_ELEMENT_ARRAY_BUFFER);
	ibo.bind();
	ibo.setData(indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

	m_transforms = new glm::mat4[MAX_CUBES];
	m_colours = new glm::vec3[MAX_CUBES];
	uint32_t width = 100;
	uint32_t height = 100;
	glm::vec3 transform{0.0f, 0.0f, 0.0f};
	for(uint32_t i = 0; i < width; i++){
		for(uint32_t j = 0; j < height; j++){
			uint32_t index = (i * width) + j;
			glm::mat4 transformMat = glm::translate(glm::mat4(1.0f), transform);
			m_transforms[index] = transformMat;
			m_colours[index] = {0.06f, 0.32f, 0.73f};
			transform.x += 1.0f;
		}
		transform.x = 0.0f;
		transform.z += 1.0f;
	}

    m_colourVbo = new VertexBuffer(GL_ARRAY_BUFFER);
	m_colourVbo->bind();
	m_colourVbo->setData(sizeof(glm::vec3) * MAX_CUBES, m_colours, GL_DYNAMIC_DRAW);
	m_vao->setAttribPointer(1, 3 , GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0, true);

    VertexBuffer transformVbo(GL_ARRAY_BUFFER);
	transformVbo.bind();
	transformVbo.setData(sizeof(glm::mat4) * MAX_CUBES, m_transforms, GL_STATIC_DRAW);

	m_vao->setAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0, true);
	m_vao->setAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)sizeof(glm::vec4), true);
	m_vao->setAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)), true);
	m_vao->setAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)), true);

	m_vao->unBind();

}

void Cube::update(float dt)
{

}

void Cube::render()
{
    m_vao->bind();
    m_colourVbo->bind();
    m_colourVbo->setData(sizeof(glm::vec3) * MAX_CUBES, m_colours, GL_DYNAMIC_DRAW);
	glDrawElementsInstanced(GL_TRIANGLES, CUBE_INDEX_COUNT, GL_UNSIGNED_INT, 0, MAX_CUBES);
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
