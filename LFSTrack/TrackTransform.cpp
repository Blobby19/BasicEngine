#include "TrackTransform.h"

namespace LFS {
	namespace Track {
		TrackTransform::TrackTransform(const std::string shortTrackName) :
			m_shortTrackName(shortTrackName)
		{

		}

		TrackTransform::~TrackTransform()
		{
			delete m_SmxFile;
		}

		void TrackTransform::init(const LFS::Format::SMX_FILE_FORMAT *smxFile)
		{
			if (m_shortTrackName.empty())
			{
				return;
			}
			m_fileName = "./tracks/" + m_shortTrackName.substr(0, 2) + "/" + TrackLoader::getTrackNameList()[m_shortTrackName] + ".obj";
			m_SmxFile = smxFile;
		}

		int TrackTransform::transform()
		{
			if (!m_SmxFile)
			{
				std::cout << "Error: No valid smxfile" << std::endl;
				return 1;
			}

			if (m_fileName.empty() || m_fileName.length() < 1)
			{
				std::cout << "Error: No filename!" << std::endl;
				return 1;
			}

			if (checkExists(m_fileName))
			{
				std::cout << "File already Exists!" << std::endl;
				return 1;
			}

			std::ofstream stream = std::ofstream(m_fileName, std::ios::out);
			if (!stream.good())
			{
				std::cout << "Error: Unable to open file" << std::endl;
				return 1;
			}

			stream << "#" <<  m_SmxFile->header.LFSSMX << "\n";

			int numberOfObjects = m_SmxFile->header.numObjects;
			int numberOfPoints = 0;
			int numberOfTriangles = 0;
			
			for (int i = 0; i < numberOfObjects; i++)
			{
				int numPoints = m_SmxFile->objects[i].numberPoints;
				int numTriangles = m_SmxFile->objects[i].numberTriangles;
				
				stream << "\ng group" << i << "\n";

				for (int j = 0; j < numPoints; j++)
				{
					stream << "v " << m_SmxFile->points[i][j].position.x / 65536.0f << " " << m_SmxFile->points[i][j].position.y / 65536.0f << " " << m_SmxFile->points[i][j].position.z / 65536.0f << "\n";
				}

				for (int j = 0; j < numTriangles; j++)
				{
					stream << "f " << m_SmxFile->triangles[i][j].vertex.a + 1 + numberOfPoints << " " << m_SmxFile->triangles[i][j].vertex.b + 1 + numberOfPoints << " " << m_SmxFile->triangles[i][j].vertex.c + 1 + numberOfPoints << "\n";
				}

				numberOfPoints += numPoints;
				numberOfTriangles += numTriangles;
			}

			stream.close();

			return 0;
		}

		bool TrackTransform::checkExists(std::string fileName)
		{
			std::ifstream fileToCheck(fileName.c_str());
			if (fileToCheck.is_open())
			{
				return true;
			}
			return false;
		}
	}
}
