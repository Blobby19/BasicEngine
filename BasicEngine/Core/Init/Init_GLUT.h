#pragma once

#include "..\ContextInfo.h"
#include "..\FrameBufferInfo.h"
#include "..\WindowInfo.h"
#include <iostream>
#include "Init_GLEW.h"

#include "..\IListener.h"
#include "DebugOutput.h"

namespace BasicEngine {
	namespace Core
	{
		namespace Init {
			class Init_GLUT;
		}
	}
}

class BasicEngine::Core::Init::Init_GLUT
{
public:
	static void setListener(Core::IListener *iListener);
	static void init(const Core::WindowInfo &windowInfo,
		const Core::ContextInfo &contextInfo,
		const Core::FrameBufferInfo &frameBufferInfo);

private:
	static Core::IListener* listener;
	static Core::WindowInfo windowInformation;

public:
	static void run();
	static void close();
	void enterFullscreen();
	void exitFullscreen();
	static void printOpenGLInfo(const Core::WindowInfo &windowInfo,
		const Core::ContextInfo &contextInfo);

private:
	static void idleCallback(void);
	static void displayCallback(void);
	static void reshapeCallback(int width, int height);
	static void closeCallback(void);
	static void keyboardCallback(unsigned char key, int x, int y);
	static void mouseCallback(int button, int state, int x, int y);
	static void motionCallback(int x, int y);
};

