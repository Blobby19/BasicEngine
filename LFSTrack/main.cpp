#include <iostream>

#include <BasicEngine\Engine.h>
#include <glm\gtc\matrix_transform.hpp>

#include "TrackLoader.h"
#include "TrackObject.h"
#include "CubeIndex.h"

int main(int argc, char **argv)
{

	BasicEngine::Engine *engine = new BasicEngine::Engine();
	engine->init();

	engine->getShaderManager()->createProgram("trackShader",
		"shaders\\cube_vertex_shader.glsl",
		"shaders\\cube_fragment_shader.glsl");

	LFS::Track::TrackLoader *loader = new LFS::Track::TrackLoader();
	loader->init();
	loader->setShortTrackName("AU3");

	LFS::Format::SMX_FILE_FORMAT smxTrack;
	loader->readTrackFile(&smxTrack);

	if (!strcmp(smxTrack.header.LFSSMX, "LFSSMX"))
	{
		std::cout << "SMX File Track loaded!" << std::endl;
	}
	else
	{
		std::cout << "Error loading file!" << std::endl;
		return -1;
	}

	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	engine->getSceneManager()->setViewMatrix(viewMatrix);
	
	TrackObject *trackObject = new TrackObject();
	trackObject->create(&smxTrack.objects[1], smxTrack.points[1], smxTrack.triangles[1]);
	trackObject->setProgram(engine->getShaderManager()->getShader("trackShader"));
	engine->getModelsManager()->setModel("track", trackObject);

	std::cout << smxTrack.points[1][0].position.x / 65536.0f << std::endl;
	std::cout << smxTrack.points[1][0].position.y / 65536.0f << std::endl;
	std::cout << smxTrack.points[1][0].position.z / 65536.0f << std::endl;

	CubeIndex *cube = new CubeIndex();
	cube->create();
	cube->setProgram(engine->getShaderManager()->getShader("trackShader"));
	engine->getModelsManager()->setModel("cube", cube);

	LFS::Format::PTH_FILE_FORMAT pthTrack;
	loader->readTrackFile(&pthTrack);

	if (!strcmp(pthTrack.header.LFSPTH, "LFSPTH"))
	{
		std::cout << "PTH File Track loaded!" << std::endl;
	}
	else
	{
		std::cout << "Error loading file!" << std::endl;
		return -1;
	}

	engine->run();

	delete engine;

	return 0;
}