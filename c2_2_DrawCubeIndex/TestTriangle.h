#pragma once

#include <BasicEngine\Rendering\Models\Model.h>
#include <time.h>
#include <stdarg.h>

class TestTriangle : public BasicEngine::Rendering::Models::Model
{
public:
	TestTriangle();
	~TestTriangle();

	void create();
	virtual void draw() override final;
	virtual void draw(
		const glm::mat4 &projection_matrix,
		const glm::mat4 &view_matrix) override final;
	virtual void update() override final;

private:
	glm::vec3 rotation, rotation_speed;
	time_t timer;
};

