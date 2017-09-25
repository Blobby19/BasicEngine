#include <iostream>

#include <BasicEngine\Engine.h>
#include <glm\gtc\matrix_transform.hpp>

#include <map>

#include "TrackLoader.h"
#include "TrackObject.h"
#include "TrackTransform.h"
#include "CubeIndex.h"

void createObjFile();

int main(int argc, char **argv)
{

	const std::string shortTrackName = "BL1";

	BasicEngine::Engine *engine = new BasicEngine::Engine();
	engine->init();

	engine->getShaderManager()->createProgram("trackShader",
		"shaders\\cube_vertex_shader.glsl",
		"shaders\\cube_fragment_shader.glsl");
	
	createObjFile();

	LFS::Track::TrackLoader *loader = new LFS::Track::TrackLoader();
	loader->init();
	loader->setShortTrackName(shortTrackName);
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
	
	TrackObject *trackObject = new TrackObject();
	trackObject->create(&smxTrack.objects[1], smxTrack.points[1], smxTrack.triangles[1]);
	trackObject->setProgram(engine->getShaderManager()->getShader("trackShader"));
	engine->getModelsManager()->setModel("track", trackObject);

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

	return 0;
}

void createObjFile()
{
	for (const auto &item : LFS::Track::TrackLoader::getTrackNameList())
	{
		std::cout << item.first << std::endl;
		LFS::Track::TrackLoader *loader = new LFS::Track::TrackLoader();
		loader->init();
		loader->setShortTrackName(item.first);
		LFS::Format::SMX_FILE_FORMAT smxTrack;
		loader->readTrackFile(&smxTrack);
		LFS::Track::TrackTransform *transform = new LFS::Track::TrackTransform(item.first);
		transform->init(&smxTrack);
		if (transform->transform())
		{
			std::cout << "Impossible to create Obj File or file already exists !" << std::endl;
			continue;
		}
	}
}