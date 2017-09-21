#pragma once

#include "Model.h"

namespace BasicEngine {
	namespace Rendering {
		namespace Models {
			class Triangle;
		}
	}
}

class BasicEngine::Rendering::Models::Triangle : public Rendering::Models::Model
{
public:
	Triangle();
	~Triangle();

	void create();
	virtual void update() override final;
	virtual void draw() override final;
};

