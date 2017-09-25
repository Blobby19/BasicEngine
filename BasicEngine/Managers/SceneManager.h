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
	void updateView();
	void showMatrix(glm::mat4 matrix);

private:
	Managers::ModelsManager *m_ModelsManager;

	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;

	bool m_MouseDown = false;
	glm::vec2 m_MousePosition;

	float yaw, pitch, roll;
	glm::vec3 eyeVector;

};

