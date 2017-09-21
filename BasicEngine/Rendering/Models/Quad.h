#pragma once

#include "Model.h"
#include <vector>

namespace BasicEngine {
	namespace Rendering
	{
		namespace Models
		{
			class Quad;
		}
	}
}

class BasicEngine::Rendering::Models::Quad : public Model
{
public:
	Quad();
	~Quad();

	void create();
	void update() override final;
	void draw() override final;
};

