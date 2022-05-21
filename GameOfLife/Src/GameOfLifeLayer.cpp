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

	glm::vec3 rayDir;
	glm::vec3 rayOrigin;
	getMouseRay(win, m_projection, m_view, rayDir, rayOrigin);
	
	bool intersect = false;
	for(uint32_t i = 0; i < MAX_CUBES; i++)
	{
		if(rayIntersect(rayDir, rayOrigin, m_cube->getTransforms()[i], *m_cube->getMin(), *m_cube->getMax()))
		{
			intersect = true;
			m_previousIntersection = m_currentIntersection;
			m_currentIntersection = i;

			m_cube->getColours()[m_previousIntersection] = {0.06f, 0.32f, 0.73f};
			m_cube->getColours()[m_currentIntersection] = {1.0f, 0.32f, 0.73f};

			if(glfwGetMouseButton(*win->getContext(), GLFW_MOUSE_BUTTON_LEFT))
			{
				m_cube->getColours()[m_currentIntersection] = {1.0f, 0.7f, 0.3f};
			}
			break;
		}
	}
	if(!intersect)
	{
		m_cube->getColours()[m_previousIntersection] = {0.06f, 0.32f, 0.73f};
	}
	

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

void GameOfLifeLayer::getMouseRay(Window* win, glm::mat4 projection, glm::mat4 view, glm::vec3& rayDir, glm::vec3& rayOrig)
{
	glm::mat4 inverseProjection = glm::inverse(projection);
	glm::mat4 inverseView = glm::inverse(view);

	double mouseX;
	double mouseY; 
	glfwGetCursorPos(*win->getContext(), &mouseX, &mouseY);

	float x = ((mouseX / win->getWidth()) - 0.5f) * 2.0f;
	float y = -((mouseY / win->getHeight()) - 0.5f) * 2.0f;

	//convert to NDC
	glm::vec4 rayStartNDC{x, y, -1.0f, 1.0f};
	glm::vec4 rayEndNDC{x, y, 0.0f, 1.0f};

	//convert from NDC to eye space
	glm::vec4 rayStartEye = inverseProjection * rayStartNDC;
	rayStartEye /= rayStartEye.w;
	glm::vec4 rayEndEye = inverseProjection * rayEndNDC;
	rayEndEye /= rayEndEye.w;

	//convert from eye space to world space
	glm::vec4 rayStartWorld = inverseView * rayStartEye;
	rayStartWorld /= rayStartWorld.w;
	glm::vec4 rayEndWorld = inverseView * rayEndEye;
	rayEndWorld /= rayEndWorld.w;

	rayDir = glm::normalize(glm::vec3{rayEndWorld - rayStartWorld});
	rayOrig = glm::vec3{rayStartWorld};
}

bool GameOfLifeLayer::rayIntersect(glm::vec3 rayDir, glm::vec3 rayOrigin, glm::mat4 transform, glm::vec3 min, glm::vec3 max)
{
	float tMin = -std::numeric_limits<float>::infinity();
	float tMax = std::numeric_limits<float>::infinity();

	glm::vec3 obb(transform[3].x, transform[3].y, transform[3].z);

	glm::vec3 delta = obb - rayOrigin;

	//check intersection with Y and Z axis
	glm::vec3 xAxis{transform[0].x, transform[0].y, transform[0].z};
	if(!perpPlaneIntersect(xAxis, delta, rayDir, min, max, tMin, tMax))
	{
		return false;
	}

	//check intersection with X and Z
	glm::vec3 yAxis(transform[1].x, transform[1].y, transform[1].z);
	if(!perpPlaneIntersect(yAxis, delta, rayDir, min, max, tMin, tMax))
	{
		return false;
	}

	//check intersection with Y and X
	glm::vec3 zAxis(transform[2].x, transform[2].y, transform[2].z);
	if(!perpPlaneIntersect(zAxis, delta, rayDir, min, max, tMin, tMax))
	{
		return false;
	}
	
	return true;
}

bool GameOfLifeLayer::perpPlaneIntersect(glm::vec3 axis, glm::vec3 delta, glm::vec3 rayDir, glm::vec3 min, glm::vec3 max, float& tMin, float& tMax)
{
	float e = glm::dot(axis, delta);
	float f = glm::dot(rayDir, axis);

	if ( fabs(f) > 0.001f )
	{

		float tNear = (e+min.x)/f;
		float tFar = (e+max.x)/f;

		if (tNear > tFar)
		{
			float temp = tFar;
			tFar = tNear;
			tNear = temp;
		}

		if (tFar < tMax)
		{
			tMax = tFar;
		}

		if (tNear > tMin )
		{
			tMin = tNear;
		}


		if (tMax < tMin )
		{
			return false;
		}

	}else
	{ 
		if(-e+min.x > 0.0f || -e+max.x < 0.0f)
		{
			return false;
		}
	}

	return true;
}
