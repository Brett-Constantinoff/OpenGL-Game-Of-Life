#include "GameOfLifeLayer.h"

GameOfLifeLayer::GameOfLifeLayer(){
}

GameOfLifeLayer::~GameOfLifeLayer(){
	delete[] m_colours;
	delete[] m_transforms;
    delete m_shader;
	delete m_textShader;
	delete m_camera;
	delete m_textRenderer;
	delete m_vbo;
	delete m_transformBuffer;
	delete m_colourBuffer;
    delete m_vao;
}

void GameOfLifeLayer::onAttach(){
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader = new Shader("GameOfLife/Assets/glsl/mainShader.glsl");
	m_textShader = new Shader("GameOfLife/Assets/glsl/textShader.glsl");

	m_textRenderer = new TextRenderer(m_textShader, 1080, 720);
	m_textRenderer->loadFont("GameOfLife/Assets/fonts/OCRAEXT.TTF", 24);

	m_camera = new Camera({0.0f, 0.0f, 7.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, 10.0f);

	m_vao = new VertexArray();
	m_vao->bind();

    float vertexData[] = {
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

	m_vbo = new VertexBuffer(GL_ARRAY_BUFFER);
	m_vbo->bind();
	m_vbo->setData(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	m_vao->setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	uint32_t indices[] = {
        0,  1,  2,      0,  2,  3,
        4,  5,  6,      4,  6,  7,   
        8,  9,  10,     8,  10, 11,  
        12, 13, 14,     12, 14, 15, 
        16, 17, 18,     17, 18, 19,  
        20, 21, 22,     21, 22, 23
    };

	VertexBuffer ibo(GL_ELEMENT_ARRAY_BUFFER);
	ibo.bind();
	ibo.setData(sizeof(indices), indices, GL_STATIC_DRAW);

	//setup platform instances
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
			m_colours[index] = {((double) rand() / (RAND_MAX)),((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX))};
			m_renderAmount++;
			transform.x += 1.0f;
		}
		transform.x = 0.0f;
		transform.z += 1.0f;
	}

	//setup instanced buffer data
	m_colourBuffer = new VertexBuffer(GL_ARRAY_BUFFER);
	m_colourBuffer->bind();
	m_colourBuffer->setData(sizeof(glm::vec3) * MAX_CUBES, m_colours, GL_DYNAMIC_DRAW);
	m_vao->setAttribPointer(1, 3 , GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0, true);

	m_transformBuffer = new VertexBuffer(GL_ARRAY_BUFFER);
	m_transformBuffer->bind();
	m_transformBuffer->setData(sizeof(glm::mat4) * MAX_CUBES, m_transforms, GL_DYNAMIC_DRAW);

	m_vao->setAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0, true);
	m_vao->setAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)sizeof(glm::vec4), true);
	m_vao->setAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)), true);
	m_vao->setAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)), true);

	m_vao->unBind();
}

void GameOfLifeLayer::onDetach(){
}

void GameOfLifeLayer::onUpdate(float dt, Window* win){
	m_camera->move(win->getContext(), dt);

	m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(win->getWidth()) / static_cast<float>(win->getHeight()), 0.1f, 500.0f);
	m_view = *m_camera->getView();

	m_frameRate.str("");
	m_frameRate << ImGui::GetIO().Framerate << " FPS";

	m_camPosition.str("");
	m_camPosition << m_camera->getPos()->x << "x " << m_camera->getPos()->y << "y " << m_camera->getPos()->z <<  "z ";

    glClearColor(0.25f, 0.25f, 0.25f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

};

void GameOfLifeLayer::onRender(){
	m_shader->use();
	m_shader->setMat4("uProjection", m_projection);
	m_shader->setMat4("uView", m_view);

    m_vao->bind();
	glDrawElementsInstanced(GL_TRIANGLES, CUBE_INDEX_COUNT, GL_UNSIGNED_INT, 0, m_renderAmount);
	m_vao->unBind();

	m_textRenderer->render(m_frameRate.str(), {0.0f, 25.0f}, 0.5f, {0.0f, 1.0f, 0.0f}, false);
	m_textRenderer->render(m_camPosition.str(), {0.0f, 45.0f}, 0.5f, {0.0f, 1.0f, 0.0f}, false);
}

void GameOfLifeLayer::onRenderImgui(){

	if (ImGui::BeginMainMenuBar()){
		if (ImGui::BeginMenu("Game Of Life Menu")){
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

}