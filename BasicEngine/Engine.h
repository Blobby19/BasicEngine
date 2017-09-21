#pragma once

#include "Core\Init\Init_GLUT.h"
#include "Managers\SceneManager.h"

namespace BasicEngine {
	class Engine;
}

class BasicEngine::Engine
{
public:
	Engine();
	~Engine();

	bool init();
	void run();

	Managers::SceneManager	*getSceneManager()		const;
	Managers::ModelsManager *getModelsManager()		const;
	Managers::ShaderManager *getShaderManager()		const;

private:
	Managers::SceneManager	*m_SceneManager;
	Managers::ModelsManager *m_ModelsManager;
	Managers::ShaderManager *m_ShaderManager;
	
};

