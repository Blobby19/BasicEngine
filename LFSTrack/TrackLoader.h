#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <map>
#include <direct.h>

#include "Smx.h"
#include "Pth.h"

#define getCurrentDir _getcwd

namespace LFS
{
	namespace Track 
	{

		enum TrackFileType {
			PTH,
			SMX
		};

		class TrackLoader
		{
		public:
			TrackLoader();
			~TrackLoader();
			void init();
			std::string getTrackDirectory();
			void setShortTrackName(const std::string &trackName);
			std::string getShortTrackName();
			static std::map<std::string, std::string> getTrackNameList();
			void readTrackFile(LFS::Format::SMX_FILE_FORMAT *fileFormat);
			void readTrackFile(LFS::Format::PTH_FILE_FORMAT *fileFormat);

		private:
			const std::string TRACK_DIRECTORY = "\\tracks\\";
			const std::string SMX_TRACK_EXTENSION = ".smx";
			const std::string PTH_TRACK_EXTENSION = ".pth";
			std::string m_shortTrackName;

		private:
			std::string getCurrentWorkingDir(void);
			std::string getTrackFilename(TrackFileType trackFileType);
		};

		static const std::map<std::string, std::string> m_trackNameList = {
			{ "AS1", "Aston_3DH" },
			{ "AS2", "Aston_3DH" },
			{ "AS3", "Aston_3DH" },
			{ "AS4", "Aston_3DH" },
			{ "AS5", "Aston_3DH" },
			{ "AS6", "Aston_3DH" },
			{ "AS7", "Aston_3DH" },
			{ "AS1R", "Aston_3DH" },
			{ "AS2R", "Aston_3DH" },
			{ "AS3R", "Aston_3DH" },
			{ "AS4R", "Aston_3DH" },
			{ "AS5R", "Aston_3DH" },
			{ "AS6R", "Aston_3DH" },
			{ "AS7R", "Aston_3DH" },
			{ "AU3", "Autocross_3DH" },
			{ "AU4", "Autocross_3DH" },
			{ "BL1", "Blackwood_3DH" },
			{ "BL2", "Blackwood_3DH" },
			{ "BL3", "Blackwood_3DH" },
			{ "BL1R", "Blackwood_3DH" },
			{ "BL2R", "Blackwood_3DH" },
			{ "BL3R", "Blackwood_3DH" },
			{ "FE1", "Fern Bay_3DH" },
			{ "FE2", "Fern Bay_3DH" },
			{ "FE3", "Fern Bay_3DH" },
			{ "FE4", "Fern Bay_3DH" },
			{ "FE5", "Fern Bay_3DH" },
			{ "FE6", "Fern Bay_3DH" },
			{ "FE1R", "Fern Bay_3DH" },
			{ "FE2R", "Fern Bay_3DH" },
			{ "FE3R", "Fern Bay_3DH" },
			{ "FE4R", "Fern Bay_3DH" },
			{ "FE5R", "Fern Bay_3DH" },
			{ "FE6R", "Fern Bay_3DH" },
			{ "KY1", "Kyoto Ring_3DH" },
			{ "KY2", "Kyoto Ring_3DH" },
			{ "KY3", "Kyoto Ring_3DH" },
			{ "KY1R", "Kyoto Ring_3DH" },
			{ "KY2R", "Kyoto Ring_3DH" },
			{ "KY3R", "Kyoto Ring_3DH" },
			{ "SO1", "South City_3DH" },
			{ "SO2", "South City_3DH" },
			{ "SO3", "South City_3DH" },
			{ "SO4", "South City_3DH" },
			{ "SO5", "South City_3DH" },
			{ "SO6", "South City_3DH" },
			{ "SO1R", "South City_3DH" },
			{ "SO2R", "South City_3DH" },
			{ "SO3R", "South City_3DH" },
			{ "SO4R", "South City_3DH" },
			{ "SO5R", "South City_3DH" },
			{ "SO6R", "South City_3DH" },
			{ "WE1", "Westhill_3DH" },
			{ "WE2", "Westhill_3DH" },
			{ "WE4", "Westhill_3DH" },
			{ "WE5", "Westhill_3DH" },
			{ "WE1R", "Westhill_3DH" },
			{ "WE2R", "Westhill_3DH" },
			{ "WE4R", "Westhill_3DH" },
			{ "WE5R", "Westhill_3DH" },

		};
	}

}