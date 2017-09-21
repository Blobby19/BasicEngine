#pragma once

#include <vector>
#include "..\IGameObject.h"

namespace BasicEngine {
	namespace Rendering {
		namespace Models {
			class Model;
		}
	}
}

class BasicEngine::Rendering::Models::Model : public IGameObject
{
public:
	Model();
	virtual ~Model();

	virtual void draw(
		const glm::mat4 &projection_matrix,
		const glm::mat4 &view_matrix) override;
	virtual void update() override;
	virtual void setProgram(GLuint shaderName) override;
	virtual void destroy() override;

	virtual GLuint getVao() const override;
	virtual const std::vector<GLuint> &getVbos() const override;

protected:
	GLuint vao;
	GLuint program;
	std::vector<GLuint> vbos;
};

