#pragma once

#ifndef VertexFormat_H_
#define VertexFormat_H_

#include "..\libs\include\glm\glm.hpp"

namespace BasicEngine {
	namespace Rendering
	{
		struct VertexFormat;
	}
}

struct BasicEngine::Rendering::VertexFormat
{
	glm::vec3 position;
	glm::vec4 color;

	VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor)
	{
		position = iPos;
		color = iColor;
	}
	VertexFormat(){}
};

#endif