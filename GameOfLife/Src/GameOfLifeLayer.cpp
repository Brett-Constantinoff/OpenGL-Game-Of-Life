#include "GameOfLifeLayer.h"

GameOfLifeLayer::GameOfLifeLayer(){
}

GameOfLifeLayer::~GameOfLifeLayer(){
    delete m_shader;
	delete m_textShader;
	delete m_camera;
	delete m_textRenderer;
	delete m_cube;

}

void GameOfLifeLayer::onAttach(){
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader = new Shader("GameOfLife/Assets/glsl/mainShader.glsl");
	m_textShader = new Shader("GameOfLife/Assets/glsl/textShader.glsl");

	m_textRenderer = new TextRenderer(m_textShader, 1080, 720);
	m_textRenderer->loadFont("GameOfLife/Assets/fonts/OCRAEXT.TTF", 24);

	m_camera = new Camera({50.0f, 53.0f, 165.2f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, 10.0f);

	m_cube = new Cube();
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

	m_shader->use();
	m_shader->setMat4("uProjection", m_projection);
	m_shader->setMat4("uView", m_view);

    glClearColor(0.25f, 0.25f, 0.25f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

};

void GameOfLifeLayer::onRender(){


	m_cube->render();

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