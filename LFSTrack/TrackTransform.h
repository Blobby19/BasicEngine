#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "TrackLoader.h"
#include "Smx.h"

namespace LFS {
	namespace Track {
		class TrackTransform
		{
		public:
			TrackTransform(const std::string shortTrackName);
			~TrackTransform();

			void init(const LFS::Format::SMX_FILE_FORMAT *smxFile);
			int transform();
			bool checkExists(std::string fileName);

		private:
			std::string m_shortTrackName;
			std::string m_fileName;
			const LFS::Format::SMX_FILE_FORMAT *m_SmxFile;
		};
	}
}

