
#include <BasicEngine\Engine.h>
#include "CubeIndex.h"
#include "TestTriangle.h"

using namespace BasicEngine;

int main(int argc, char **argv)
{
	Engine *engine = new Engine();

	engine->init();

	engine->getShaderManager()->createProgram("cubeShader",
		"shaders\\cube_vertex_shader.glsl",
		"shaders\\cube_fragment_shader.glsl");

	CubeIndex *cubeindex = new CubeIndex();

	cubeindex->setProgram(engine->getShaderManager()->getShader("cubeShader"));
	cubeindex->create();

	engine->getModelsManager()->setModel("cubeindex", cubeindex);

	engine->run();

	delete engine;
	return 0;
}