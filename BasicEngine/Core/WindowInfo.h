#pragma once

#include <string>

namespace BasicEngine {
	namespace Core {
		struct WindowInfo;
	}
}

struct BasicEngine::Core::WindowInfo
{
	std::string name;
	int width, height;
	int position_x, position_y;
	bool isReshapable;

	WindowInfo()
	{
		name = "LFS Window";
		width = 800; height = 600;
		position_x = 300;
		position_y = 300;
		isReshapable = true;
	}

	WindowInfo(std::string name,
		int start_position_x, int start_position_y,
		int width, int height,
		bool is_reshapable)
	{
		this->name = name;
		this->position_x = start_position_x;
		this->position_y = start_position_y;
		this->width = width;
		this->height = height;
		this->isReshapable = is_reshapable;
	}

	//copy construcor
	WindowInfo(const WindowInfo &windowInfo)
	{
		name = windowInfo.name;
		position_x = windowInfo.position_x;
		position_y = windowInfo.position_y;
		width = windowInfo.width;
		height = windowInfo.height;
		isReshapable = windowInfo.isReshapable;
	}

	void operator=(const WindowInfo &windowInfo)
	{
		name = windowInfo.name;
		position_x = windowInfo.position_x;
		position_y = windowInfo.position_y;
		width = windowInfo.width;
		height = windowInfo.height;
		isReshapable = windowInfo.isReshapable;
	}

};
