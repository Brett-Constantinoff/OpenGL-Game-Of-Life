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
	m_textRenderer->loadFont("GameOfLife/Assets/fonts/OpenSans-Regular.TTF", 24);

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

	double mouseX;
	double mouseY;
	glm::vec3 rayOut;
	glm::vec3 rayOrigin;
	glfwGetCursorPos(*win->getContext(), &mouseX,  &mouseY);
	getMouseRay(
		{mouseX, mouseY},
		{win->getWidth(), win->getHeight()},
		m_projection, 
		m_view, 
		rayOut, 
		rayOrigin
	);

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

void GameOfLifeLayer::getMouseRay(
	glm::vec2 mouseCoord,
	glm::vec2 screenDim, 
	glm::mat4 projection, 
	glm::mat4 view, 
	glm::vec3& rayOut, 
	glm::vec3& rayOrigin)
{
	//sreen coord to NDC
	glm::vec4 rayStart{
		(static_cast<float>(mouseCoord.x) / static_cast<float>(screenDim.x) - 0.5f) * 2.0f,
		(static_cast<float>(mouseCoord.y) / static_cast<float>(screenDim.y) - 0.5f) * 2.0f,
		-1.0f, 
		1.0f
	};

	glm::vec4 rayEnd{
		rayStart.x, 
		rayStart.y, 
		0.0f, 
		1.0f
	};

	glm::mat4 inverseProjection = glm::inverse(projection);
	glm::mat4 inverseView = glm::inverse(view);

	//cam space to world space
	glm::vec4 rayStartCamSpace = inverseProjection * rayStart;
	rayStartCamSpace /= rayStartCamSpace.w;
	glm::vec4 rayStartWorldSpace = inverseView * rayStartCamSpace;
	rayStartWorldSpace /= rayStartWorldSpace.w;

	glm::vec4 rayEndCamSpace = inverseProjection * rayEnd;
	rayEndCamSpace /= rayEndCamSpace.w;
	glm::vec4 rayEndWorldSpace = inverseView * rayEndCamSpace;
	rayEndWorldSpace /= rayEndWorldSpace.w;

	glm::vec3 rayDir = rayEndWorldSpace - rayStartWorldSpace;

	rayDir = glm::normalize(rayDir);
	rayOut = glm::vec3(rayStartWorldSpace);
}
