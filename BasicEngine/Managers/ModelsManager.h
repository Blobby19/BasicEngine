#pragma once

#include <map>
#include "ShaderManager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"

namespace BasicEngine {
	namespace Managers {
		class ModelsManager;
	}
}

class BasicEngine::Managers::ModelsManager
{
public:
	ModelsManager();
	~ModelsManager();

	void draw();
	void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);

	void update();
	void deleteModel(const std::string &gameModelName);
	const Rendering::IGameObject &getModel(const std::string &gameModelName) const;

	void setModel(const std::string &gameObjectName, 
		Rendering::IGameObject *gameObject);

private:
	std::map<std::string, Rendering::IGameObject*> gameModelList;
};

