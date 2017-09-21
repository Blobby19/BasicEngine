#include "TestTriangle.h"

using namespace BasicEngine::Rendering;
using namespace BasicEngine::Rendering::Models;

TestTriangle::TestTriangle()
{
}


TestTriangle::~TestTriangle()
{
}

void TestTriangle::create()
{

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	time(&timer);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<unsigned int> indices = {
		0,	1,	2,	
		1,	3,	2
	};

	std::vector<VertexFormat> vertices;
	//front
	vertices.push_back(VertexFormat(glm::vec3(-631.65, -381.01, 9.29094),
		glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-631.65, -381.01, 11.8439),
		glm::vec4(1, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-631.18, -381.009, 11.8439),
		glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-631.18, -381.009, 13.5551),
		glm::vec4(1, 1, 1, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	//rotation_speed = glm::vec3(9.0, 9.0, 9.0);
	//rotation = glm::vec3(0.0, 0.0, 0.0);

}

void TestTriangle::draw()
{
}

void TestTriangle::draw(const glm::mat4 & projection_matrix, const glm::mat4 & view_matrix)
{
	//rotation = 0.01f * rotation_speed + rotation;

	//glm::vec3 rotation_sin = glm::vec3(rotation.x * PI / 180,
	//	rotation.y * PI / 180, rotation.z * PI / 180);

	glUseProgram(program);
	//glUniform3f(glGetUniformLocation(program, "rotation"),
	//	rotation.x,
	//	rotation.y,
	//	rotation.z);

	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &view_matrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1,
		false, &projection_matrix[0][0]);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
}

void TestTriangle::update()
{
}
