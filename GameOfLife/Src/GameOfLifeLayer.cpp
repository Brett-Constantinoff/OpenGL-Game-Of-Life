#include "GameOfLifeLayer.h"

GameOfLifeLayer::GameOfLifeLayer()
{
}

GameOfLifeLayer::~GameOfLifeLayer()
{
    delete m_shader;
	delete m_textShader;
	delete m_camera;
	delete m_textRenderer;
	delete m_cube;
	delete m_mousePicker;
	delete m_board;
}

void GameOfLifeLayer::onAttach()
{
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader = new Shader("GameOfLife/Assets/glsl/mainShader.glsl");
	m_textShader = new Shader("GameOfLife/Assets/glsl/textShader.glsl");

	m_textRenderer = new TextRenderer(m_textShader, 1080, 720);
	m_textRenderer->loadFont("GameOfLife/Assets/fonts/OpenSans-Regular.TTF", 24);

	m_camera = new Camera({49.86f, 108.20f, -6.55f}, {0.0f, -0.91f, 0.41f}, {0.0f, 1.0f, 0.0f}, 10.0f);

	m_cube = new Cube();
	
	m_mousePicker = new MousePicker(0.10f);

	m_state = State::DEFAULT;

	m_board = new Board(100, 100);

}

void GameOfLifeLayer::onDetach()
{
}

void GameOfLifeLayer::onUpdate(float dt, Window* win)
{

	m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(win->getWidth()) / static_cast<float>(win->getHeight()), 0.1f, 500.0f);
	m_view = *m_camera->getView();

	m_frameRate.str("");
	m_frameRate << ImGui::GetIO().Framerate << " FPS";

	m_spawnedObjects.str("");
	m_spawnedObjects << "Objects: " <<  *m_cube->getRenderAmount() - PLATFORM_CUBES;

	m_generation.str("");
	m_generation << "Generation: " << m_currentGen;

	m_shader->use();
	m_shader->setMat4("uProjection", m_projection);
	m_shader->setMat4("uView", m_view);


	m_mousePicker->getMouseRay(win, m_projection, m_view);

	
	bool intersect = false;
	for(int i = 0; i < *m_cube->getRenderAmount(); i++)
	{
		if(m_mousePicker->rayIntersectCube(m_cube->getTransforms()[i], *m_cube->getMin(), *m_cube->getMax()))
		{
			intersect = true;
			m_previousIntersection = m_currentIntersection;
			m_currentIntersection = i;

			//change previous intersection so cubes arent being continuously coloured
			m_cube->getColours()[m_previousIntersection] = *m_cube->getStandarColour();
			m_cube->getColours()[m_currentIntersection] = *m_cube->getSelectionColour();

			if(glfwGetMouseButton(*win->getContext(), GLFW_MOUSE_BUTTON_LEFT))
			{
				float currentClick = glfwGetTime();
				float dt = currentClick - m_lastClick;
				m_lastClick = currentClick;
				
				if(dt >= m_mousePicker->getClickSpeed())
				{
					glm::vec3 cellPosition{m_cube->getPositions()[i].x,  m_cube->getPositions()[i].y + 1.0f, m_cube->getPositions()[i].z};

					int index = m_cube->getIndex(cellPosition);
					if(index != -1)
					{
						m_cube->removeInstance(index);
					}
					else
					{
						m_cube->addInstance(cellPosition);
					}
				}
			}
			break;
			
		}
	}
	if(!intersect)
	{
		m_cube->getColours()[m_previousIntersection] = *m_cube->getStandarColour();
	}
	
	if(m_state == State::RESET)
	{
		m_cube->removeCells();
		m_state = State::DEFAULT;
	}

	if(m_state == State::RUNNING)
	{
		m_board->solve(m_cube);
		m_currentGen++;
	}
	
    glClearColor(0.25f, 0.25f, 0.25f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void GameOfLifeLayer::onRender()
{
	m_cube->render();

	m_textRenderer->render(m_frameRate.str(), {0.0f, 25.0f}, 0.5f, {0.0f, 1.0f, 0.0f}, false);
	m_textRenderer->render(m_spawnedObjects.str(), {0.0f, 45.0f}, 0.5f, {0.0f, 1.0f, 0.0f}, false);
	m_textRenderer->render(m_generation.str(), {0.0f, 65.0f}, 0.5f, {0.0f, 1.0f, 0.0f}, false);
}

void GameOfLifeLayer::onRenderImgui()
{

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Game Of Life Menu"))
		{
			if(ImGui::MenuItem("Begin Game of Life"))
			{
				m_state = State::RUNNING;
			}
			if(ImGui::MenuItem("Reset Game of Life"))
			{
				m_state = State::RESET;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}



