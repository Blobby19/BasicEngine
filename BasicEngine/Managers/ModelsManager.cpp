#include "ModelsManager.h"

using namespace BasicEngine::Managers;
using namespace BasicEngine::Rendering;

ModelsManager::ModelsManager()
{
	
}


ModelsManager::~ModelsManager()
{
	for (auto model : gameModelList)
	{
		delete model.second;
	}

	gameModelList.clear();
}


void ModelsManager::draw()
{
	for (auto model : gameModelList)
	{
		model.second->draw();
	}
}

void ModelsManager::draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix)
{
	for (auto model : gameModelList)
	{
		model.second->draw(projection_matrix, view_matrix);
	}
}

void ModelsManager::update()
{
	for (auto model : gameModelList)
	{
		model.second->update();
	}
}

void ModelsManager::deleteModel(const std::string & gameModelName)
{
	IGameObject *model = gameModelList[gameModelName];
	model->destroy();
	gameModelList.erase(gameModelName);
}

const IGameObject &ModelsManager::getModel(const std::string & gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

void ModelsManager::setModel(const std::string &gameObjectName, 
	IGameObject *gameObject)
{
	gameModelList[gameObjectName.c_str()] = gameObject;
}
