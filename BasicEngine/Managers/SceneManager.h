#pragma once

#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Core/IListener.h"

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

	virtual void notifyBeginFrame();
	virtual void notifyDisplayFrame();
	virtual void notifyEndFrame();
	virtual void notifyReshape(int width, int height,
		int previous_width, int previous_height);

	void setModelsManager(Managers::ModelsManager *&_modelsManager);
	void setViewMatrix(glm::mat4 viewMatrix);
	void setProjectionMatrix(glm::mat4 projectionMatrix);

private:
	Managers::ModelsManager *modelsManager;

	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
};

