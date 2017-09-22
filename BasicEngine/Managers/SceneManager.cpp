#include "SceneManager.h"

using namespace BasicEngine::Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	view_matrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);

	modelsManager = new ModelsManager();
}


SceneManager::~SceneManager()
{
	delete modelsManager;
	modelsManager = nullptr;
}

void SceneManager::notifyBeginFrame()
{
	//notify here for the moment
	modelsManager->update();
}

void SceneManager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	modelsManager->draw();
	modelsManager->draw(projection_matrix, view_matrix);
}

void SceneManager::notifyEndFrame()
{
	//nothing here for the moment
}

void SceneManager::notifyReshape(int width, int height, int previous_width, int previous_height)
{
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projection_matrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projection_matrix[1][1] = 1.0f / tan(angle / 2.0f);
	projection_matrix[2][2] = (-near1 - far1) / (near1 - far1);
	projection_matrix[2][3] = 1.0f;
	projection_matrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
}

void SceneManager::setModelsManager(ModelsManager *& _modelsManager)
{
	modelsManager = _modelsManager;
}

void BasicEngine::Managers::SceneManager::setViewMatrix(glm::mat4 viewMatrix)
{
	view_matrix = viewMatrix;
}

void BasicEngine::Managers::SceneManager::setProjectionMatrix(glm::mat4 projectionMatrix)
{
	projection_matrix = projectionMatrix;
}
