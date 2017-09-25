#include "SceneManager.h"

using namespace BasicEngine::Managers;

SceneManager::SceneManager():
	m_ModelsManager(nullptr)
{
	glEnable(GL_DEPTH_TEST);

	m_ViewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);

	m_ModelsManager = new ModelsManager();
}


SceneManager::~SceneManager()
{
	delete m_ModelsManager;
	m_ModelsManager = nullptr;
}

void SceneManager::notifyBeginFrame()
{
	//notify here for the moment
	m_ModelsManager->update();
}

void SceneManager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	m_ModelsManager->draw();
	m_ModelsManager->draw(m_ProjectionMatrix, m_ViewMatrix);
}

void SceneManager::notifyEndFrame()
{
	//nothing here for the moment
}

void SceneManager::notifyReshape(int width, int height, int previous_width, int previous_height)
{
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	m_ProjectionMatrix = glm::perspective(angle, ar, near1, far1);

	/*
	projection_matrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projection_matrix[1][1] = 1.0f / tan(angle / 2.0f);
	projection_matrix[2][2] = (-near1 - far1) / (near1 - far1);
	projection_matrix[2][3] = 1.0f;
	projection_matrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
	*/
}

void SceneManager::notifyMouse(int button, int state, int x, int y)
{
	std::cout << "notifyMouse" << std::endl;
	if (state == GLUT_UP)
		m_MouseDown = false;
	if (state == GLUT_DOWN)
	{
		m_MouseDown = true;
		m_MousePosition.x = x;
		m_MousePosition.y = y;
	}
}

void SceneManager::notifyKeyboard(unsigned char key, int x, int y)
{
	std::cout << "notifyKeyboard" << std::endl;

	float dx = 0, dz = 0;
	switch(key)
	{
	case 'z':
		dz = 2;
		break;
	case 's':
		dz = -2;
		break;
	case 'q':
		dx = -2;
		break;
	case 'd':
		dx = 2;
		break;
	default:
		break;
	}

	glm::mat4 mat = getViewMatrix();

	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.12f;

	eyeVector += (-dz * forward + dx * strafe) * speed;

	updateView();
}

void SceneManager::notifyPassiveMotion(int x, int y)
{
	if (!m_MouseDown) return;

	std::cout << "notifyPassiveMotion" << std::endl;
	glm::vec2 mouse_delta = glm::vec2(x, y) - m_MousePosition;

	const float mouseX_sensitivity = 0.25f;
	const float mouseY_sensitivity = 0.25f;

	std::cout << mouse_delta.x << std::endl;

	yaw += mouseX_sensitivity * mouse_delta.x;
	pitch += mouseY_sensitivity * mouse_delta.y;

	std::cout << yaw << " - " << pitch << std::endl;

	m_MousePosition = glm::vec2(x, y);

	updateView();
}

void SceneManager::setModelsManager(ModelsManager *& _modelsManager)
{
	m_ModelsManager = _modelsManager;
}

glm::mat4 BasicEngine::Managers::SceneManager::getViewMatrix()
{
	return m_ViewMatrix;
}

void BasicEngine::Managers::SceneManager::setViewMatrix(glm::mat4 viewMatrix)
{
	m_ViewMatrix = viewMatrix;
}

void BasicEngine::Managers::SceneManager::setProjectionMatrix(glm::mat4 projectionMatrix)
{
	m_ProjectionMatrix = projectionMatrix;
}

void SceneManager::updateView()
{
	glm::mat4 matRoll	= glm::mat4(1.0f);
	glm::mat4 matPitch	= glm::mat4(1.0f);
	glm::mat4 matYaw	= glm::mat4(1.0f);

	//std::cout << "yaw: " << yaw << " - pitch: " << pitch << std::endl;

	matRoll		= glm::rotate(matRoll, roll, glm::vec3(0.0f, 0.0f, 1.0f));
	matPitch	= glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw		= glm::rotate(matYaw, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 rotate = matRoll * matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);

	translate = glm::translate(translate, -eyeVector);

	setViewMatrix(rotate * translate);
}

void SceneManager::showMatrix(glm::mat4 matrix)
{
	std::cout << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << " " << matrix[0][3] << std::endl;
	std::cout << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << " " << matrix[3][3] << std::endl;
	std::cout << matrix[2][0] << " " << matrix[2][1] << " " << matrix[2][2] << " " << matrix[3][3] << std::endl;
	std::cout << matrix[3][0] << " " << matrix[3][1] << " " << matrix[3][2] << " " << matrix[3][3] << std::endl;
}
