#pragma once

#include "time.h"

#include "TrackLoader.h"

namespace LFS
{
	namespace Track
	{
		TrackLoader::TrackLoader()
			:m_shortTrackName()
		{

		}

		TrackLoader::~TrackLoader()
		{
		}

		void TrackLoader::init()
		{

		}

		std::string TrackLoader::getTrackDirectory()
		{
			std::stringstream stream;
			stream << getCurrentWorkingDir() << TRACK_DIRECTORY;
			return stream.str();
		}
		
		void TrackLoader::setShortTrackName(const std::string & trackName)
		{
			m_shortTrackName = trackName;
		}

		std::string TrackLoader::getShortTrackName()
		{
			return m_shortTrackName;
		}

		std::map<std::string, std::string> TrackLoader::getTrackNameList()
		{
			return m_trackNameList;
		}

		void TrackLoader::readTrackFile(LFS::Format::SMX_FILE_FORMAT *fileFormat)
		{
			if (m_shortTrackName.empty())
			{
				std::cout << "Track unavailable!" << std::endl;
				return;
			}
			std::cout << "Track selected: " << m_shortTrackName.c_str() << std::endl;
			std::string smxTrackFilename = getTrackFilename(TrackFileType::SMX);
			std::ifstream file(smxTrackFilename, std::ios::binary);
			if (!file.good())
			{
				std::cout << "File unavailable!" << std::endl;
				return;
			}

			clock_t start = clock();

			long numberOfVertices = 0;
			long numberOfTriangles = 0;

			file.seekg(0, std::ios::beg);
			file.read(reinterpret_cast<char *> (&fileFormat->header), sizeof(fileFormat->header));
			fileFormat->objects = new LFS::Format::SMX_OBJECT_BLOCK[fileFormat->header.numObjects];
			fileFormat->points = (LFS::Format::SMX_POINT_BLOCK**)malloc(sizeof(LFS::Format::SMX_POINT_BLOCK*) * fileFormat->header.numObjects);
			fileFormat->triangles = (LFS::Format::SMX_TRIANGLE_BLOCK**)malloc(sizeof(LFS::Format::SMX_TRIANGLE_BLOCK*) * fileFormat->header.numObjects);
			for (int i = 0; i < fileFormat->header.numObjects; i++){
				file.read(reinterpret_cast<char *>(&fileFormat->objects[i]), sizeof(LFS::Format::SMX_OBJECT_BLOCK));
				fileFormat->points[i] = new LFS::Format::SMX_POINT_BLOCK[fileFormat->objects[i].numberPoints];
				fileFormat->triangles[i] = new LFS::Format::SMX_TRIANGLE_BLOCK[fileFormat->objects[i].numberTriangles];
				for (int j = 0; j < fileFormat->objects[i].numberPoints; j++)
				{
					numberOfVertices += 3;
					file.read(reinterpret_cast<char *>(&fileFormat->points[i][j]), sizeof(LFS::Format::SMX_POINT_BLOCK));
				}
				for (int j = 0; j < fileFormat->objects[i].numberTriangles; j++)
				{
					numberOfTriangles++;
					file.read(reinterpret_cast<char *>(&fileFormat->triangles[i][j]), sizeof(LFS::Format::SMX_TRIANGLE_BLOCK));
				}
			}
			file.read(reinterpret_cast<char *>(&fileFormat->numberCheckpointObjects), sizeof(fileFormat->numberCheckpointObjects));
			fileFormat->objectIndex = new int[fileFormat->numberCheckpointObjects];
			for (int i = 0; i < fileFormat->numberCheckpointObjects; i++)
				file.read(reinterpret_cast<char *>(&fileFormat->objectIndex[i]), sizeof(fileFormat->objectIndex));
			
			file.close();

			std::cout << "Nombre de Vertices: " << numberOfVertices << std::endl;
			std::cout << "Nombre de Triangles: " << numberOfTriangles << std::endl;

			std::cout << "Reading track time: " << clock() - start << "ms" << std::endl;
		}

		void TrackLoader::readTrackFile(LFS::Format::PTH_FILE_FORMAT *fileFormat)
		{
			if (m_shortTrackName.empty())
			{
				std::cout << "Track unavailable!" << std::endl;
				return;
			}
			std::cout << "Track selected: " << m_shortTrackName.c_str() << std::endl;
			std::string pthTrackFilename = getTrackFilename(TrackFileType::PTH);
			std::ifstream file(pthTrackFilename, std::ios::binary);
			if (!file.good())
			{
				std::cout << "File unavailable!" << std::endl;
				return;
			}

			clock_t start = clock();

			file.seekg(0, std::ios::beg);
			file.read(reinterpret_cast<char *> (&fileFormat->header), sizeof(fileFormat->header));
			
			fileFormat->nodes = new LFS::Format::PTH_NODE[fileFormat->header.numberNodes];
			for (int i = 0; i < fileFormat->header.numberNodes; i++) {
				file.read(reinterpret_cast<char *>(&fileFormat->nodes[i]), sizeof(LFS::Format::PTH_NODE));
			}

			file.close();

			std::cout << "Reading track time: " << clock() - start << "ms" << std::endl;
		}

		std::string TrackLoader::getTrackFilename(TrackFileType trackFileType)
		{
			std::stringstream stream;
			stream << getTrackDirectory() << getShortTrackName().substr(0, 2) << '\\'
				<< ((trackFileType == TrackFileType::PTH)?getShortTrackName():m_trackNameList[getShortTrackName()])
				<< ((trackFileType == TrackFileType::PTH)? PTH_TRACK_EXTENSION:SMX_TRACK_EXTENSION);
			return stream.str();
		}

		std::string TrackLoader::getCurrentWorkingDir(void)
		{
			char buf[FILENAME_MAX];
			getCurrentDir(buf, FILENAME_MAX);
			std::string currentWorkingDir(buf);
			return currentWorkingDir;
		}
	}
}