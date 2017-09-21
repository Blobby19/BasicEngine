#pragma once

#include <math.h>
#include <vector>
#include <iostream>

#include "..\libs\include\glew\glew.h"
#include "..\libs\include\freeglut\freeglut.h"
#include "VertexFormat.h"

#define PI 3.14159265358979323846

namespace BasicEngine {
	namespace Rendering {
		class IGameObject;
	}
}

class BasicEngine::Rendering::IGameObject
{
public:
	virtual ~IGameObject() = 0;
	
	virtual void draw() = 0;
	virtual void draw(const glm::mat4 &projection_matrix,
		const glm::mat4 &view_matrix) = 0;
	virtual void update() = 0;
	virtual void setProgram(GLuint shaderName) = 0;
	virtual void destroy() = 0;

	virtual GLuint getVao() const = 0;
	virtual const std::vector<GLuint> &getVbos() const = 0;
};

inline BasicEngine::Rendering::IGameObject::~IGameObject(){}