#pragma once

#include <BasicEngine\Rendering\Models\Model.h>

#include "Smx.h"

class TrackObject : public BasicEngine::Rendering::Models::Model
{
public:
	TrackObject();
	~TrackObject();

	void create(const LFS::Format::SMX_OBJECT_BLOCK *object, 
		const LFS::Format::SMX_POINT_BLOCK *points, 
		const LFS::Format::SMX_TRIANGLE_BLOCK *triangle);
	void draw() override final;
	void draw(const glm::mat4 &projectionMatrix,
		const glm::mat4 &viewMatrix) override final;
	void update() override final;


private:
	glm::vec3 rotation, rotation_speed;
	int m_numberOfVertices = 0;

};

