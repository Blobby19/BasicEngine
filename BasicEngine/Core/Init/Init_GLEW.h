#pragma once

#include <iostream>
#include <glew\glew.h>
#include <freeglut\freeglut.h>

namespace BasicEngine {
	namespace Core
	{
		namespace Init {
			class Init_GLEW;
		}
	}
}

class BasicEngine::Core::Init::Init_GLEW
{
public:
	static void Init();
};

