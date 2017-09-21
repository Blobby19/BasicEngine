#include "TrackObject.h"

using namespace BasicEngine::Rendering::Models;
using namespace BasicEngine::Rendering;

TrackObject::TrackObject()
{
}


TrackObject::~TrackObject()
{
}

void TrackObject::create(const LFS::Format::SMX_OBJECT_BLOCK *object, 
	const LFS::Format::SMX_POINT_BLOCK *points, 
	const LFS::Format::SMX_TRIANGLE_BLOCK *triangle)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices = { 0 };
	indices.reserve(sizeof(unsigned int) * object->numberTriangles * 3);
	m_numberOfVertices = object->numberPoints;
	for (int i = 0; i<  object->numberPoints; i++)
	{
		vertices.push_back(VertexFormat(
			glm::vec3(points[i].position.x, points[i].position.y, points[i].position.z), 
			glm::vec4((points[i].color & 0xFF0000), (points[i].color & 0x00FF00), (points[i].color & 0x0000FF), 1.0f)));
	}

	for (int i = 0; i < object->numberTriangles; i++)
	{
		indices.push_back(triangle[i].vertex.a);
		indices.push_back(triangle[i].vertex.b);
		indices.push_back(triangle[i].vertex.c);
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * object->numberPoints, &indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::position)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
}

void TrackObject::draw()
{
}

void TrackObject::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix)
{
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "rotation"),
		rotation.x,
		rotation.y,
		rotation.z);

	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &viewMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1,
		false, &projectionMatrix[0][0]);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, m_numberOfVertices, GL_UNSIGNED_INT, 0);
}

void TrackObject::update()
{

}
