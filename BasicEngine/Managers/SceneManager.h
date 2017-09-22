#pragma once

#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Core/IListener.h"

#include <glm\gtc\matrix_transform.hpp>

namespace BasicEngine {
	namespace Managers {
		class SceneManager;
	}
}
class BasicEngine::Managers::SceneManager 
	: public BasicEngine::Core::IListener
{
public:
	SceneManager();
	~SceneManager();

	virtual void notifyBeginFrame() override;
	virtual void notifyDisplayFrame() override;
	virtual void notifyEndFrame() override;
	virtual void notifyReshape(int width, 
		int height,
		int previous_width, 
		int previous_height) override;
	virtual void notifyMouse(int button, 
		int state, int x, int y) override;
	virtual void notifyKeyboard(unsigned char key, 
		int x, int y) override;
	virtual void notifyPassiveMotion(int x, int y) override;

	void setModelsManager(Managers::ModelsManager *&_modelsManager);
	glm::mat4 getViewMatrix();
	void setViewMatrix(glm::mat4 viewMatrix);
	void setProjectionMatrix(glm::mat4 projectionMatrix);

private:
	Managers::ModelsManager *modelsManager;

	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;

	bool mouseDown = false;
	glm::vec2 mousePosition;

	float yaw, pitch, roll;
	glm::vec3 eyeVector;

};

