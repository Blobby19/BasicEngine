#include "Engine.h"

using namespace BasicEngine;
using namespace Core;
using namespace Init;

Engine::Engine():
	m_SceneManager(nullptr),
	m_ModelsManager(nullptr),
	m_ShaderManager(nullptr)
{
}


Engine::~Engine()
{
	if (m_SceneManager)
		delete m_SceneManager;
	if (m_ModelsManager)
		delete m_ModelsManager;
	if (m_ShaderManager)
		delete m_ShaderManager;
}

bool Engine::init()
{
	WindowInfo window(std::string("in2gpu OpenGL Beginner"),
		400, 200,
		800, 600,
		true);

	ContextInfo context(4, 5, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);

	Init_GLUT::init(window, context, frameBufferInfo);

	m_SceneManager = new Managers::SceneManager();
	Init_GLUT::setListener(m_SceneManager);

	m_ShaderManager = new Managers::ShaderManager();
	m_ShaderManager->createProgram("colorShader",
		"..\\BasicEngine\\shaders\\vertex_shader.glsl",
		"..\\BasicEngine\\shaders\\fragment_shader.glsl");

	if (m_SceneManager && m_ShaderManager)
	{
		m_ModelsManager = new Managers::ModelsManager();
		m_SceneManager->setModelsManager(m_ModelsManager);
	}
	else return false;

	return true;
}

void Engine::run()
{
	Init_GLUT::run();
}

Managers::SceneManager *Engine::getSceneManager() const
{
	return m_SceneManager;
}

Managers::ModelsManager *Engine::getModelsManager() const
{
	return m_ModelsManager;
}

Managers::ShaderManager *Engine::getShaderManager() const
{
	return m_ShaderManager;
}


