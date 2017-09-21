#include "Model.h"

using namespace BasicEngine::Rendering::Models;

Model::Model() {}

Model::~Model() {}

void Model::draw(const glm::mat4 & projection_matrix, 
	const glm::mat4 & view_matrix)
{
}

void Model::update()
{

}

void Model::setProgram(GLuint program) 
{
	this->program = program;
}

GLuint Model::getVao() const
{
	return vao;
}

const std::vector<GLuint> &Model::getVbos() const
{
	return vbos;
}

void Model::destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}