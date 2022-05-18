#include "GameOfLifeLayer.h"

GameOfLifeLayer::GameOfLifeLayer(){

}

GameOfLifeLayer::~GameOfLifeLayer(){
    delete m_shader;
	delete m_textShader;
	delete m_camera;
	delete m_textRenderer;
    glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);

}

void GameOfLifeLayer::onAttach(){
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader = new Shader("GameOfLife/Assets/glsl/mainShader.glsl");
	m_textShader = new Shader("GameOfLife/Assets/glsl/textShader.glsl");

	m_camera = new Camera({0.0f, 0.0f, 7.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f});

	m_quadColour = {0.34f, 0.57f, 0.89f};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	uint32_t indices[] = {
         0, 1, 2,
         2, 3, 0 
    };

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_textRenderer = new TextRenderer(m_textShader, 1080, 720);
	m_textRenderer->loadFont("GameOfLife/Assets/fonts/OCRAEXT.TTF", 24);
}

void GameOfLifeLayer::onDetach(){

}

void GameOfLifeLayer::onUpdate(float dt, Window* win){
	m_camera->move(win->getContext(), dt);

	m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(win->getWidth()) / static_cast<float>(win->getHeight()), 0.1f, 100.0f);
	m_view = *m_camera->getView();
    glClearColor(0.25f, 0.25f, 0.25f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_frameRate.str("");
	m_frameRate << ImGui::GetIO().Framerate << " FPS";
};

void GameOfLifeLayer::onRender(){
	glUseProgram(m_shader->getId());

	m_shader->setMat4("uProjection", m_projection);
	m_shader->setMat4("uView", m_view);

	m_shader->setVec3("uColour", m_quadColour);

    glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	m_textRenderer->render(m_frameRate.str(), {0.0f, 30.0f}, 0.5f, {0.0f, 1.0f, 0.0f}, false);
}

void GameOfLifeLayer::onRenderImgui(){


    ImGui::Begin("Main Window");

	if (ImGui::BeginMainMenuBar()){
		if (ImGui::BeginMenu("This is a menu button")){
			if (ImGui::MenuItem("Hello!")){
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::ColorEdit3("Quad Colour", &m_quadColour[0]);
    ImGui::End();
}