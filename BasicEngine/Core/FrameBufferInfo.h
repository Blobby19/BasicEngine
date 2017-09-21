#pragma once

#include <glew/glew.h>
#include <freeglut/freeglut.h>

namespace BasicEngine {
	namespace Core {
		struct FrameBufferInfo;
	}
}

struct BasicEngine::Core::FrameBufferInfo
{
	unsigned int flags;
	bool msaa; //to enable or disable it when we need it

	FrameBufferInfo()
	{
		//defaults
		flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
		msaa = false;
	}

	FrameBufferInfo(bool color, bool depth, bool stencil, bool msaa)
	{
		flags = GLUT_DOUBLE;	//this is a must
		if (color)
			flags |= GLUT_RGBA | GLUT_ALPHA;
		if (depth)
			flags |= GLUT_DEPTH;
		if (stencil)
			flags |= GLUT_STENCIL;
		if (msaa)
			flags |= GLUT_MULTISAMPLE;
		this->msaa = msaa;
	}

	FrameBufferInfo(const FrameBufferInfo &frameBufferInfo)
	{
		flags = frameBufferInfo.flags;
		msaa = frameBufferInfo.msaa;
	}

	void operator=(const FrameBufferInfo &frameBufferInfo)
	{
		flags = frameBufferInfo.flags;
		msaa = frameBufferInfo.msaa;
	}
};