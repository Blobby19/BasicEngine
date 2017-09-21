#include "Init_GLUT.h"

using namespace BasicEngine::Core;
using namespace BasicEngine::Core::Init;

IListener *Init_GLUT::listener = NULL;
WindowInfo Init_GLUT::windowInformation;

void Init_GLUT::setListener(IListener *iListener)
{
	listener = iListener;
}

void Init_GLUT::init(
	const WindowInfo & windowInfo,
	const ContextInfo & contextInfo, 
	const FrameBufferInfo & frameBufferInfo)
{
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };

	glutInit(&fakeargc, fakeargv);

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.major_version,
			contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(frameBufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x, 
		windowInfo.position_y);
	glutInitWindowSize(windowInfo.width,
		windowInfo.height);
	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT: Initialized" << std::endl;

	glEnable(GL_DEBUG_OUTPUT);

	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	windowInformation = windowInfo;

	Init_GLEW::Init();
	glDebugMessageCallback(DebugOutput::callback, NULL);
	glDebugMessageControl(GL_DONT_CARE,
		GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, 
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	printOpenGLInfo(windowInfo, contextInfo);
}

void Init_GLUT::run()
{
	std::cout << "GLUT:\tStart Running " << std::endl;
	glutMainLoop();
}

void Init_GLUT::close()
{
	std::cout << "GLUT:\tFinished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::enterFullscreen()
{
	glutFullScreen();
}

void Init_GLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void Init_GLUT::printOpenGLInfo(const WindowInfo & windowInfo, const ContextInfo & contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************               ************************" << std::endl;
	std::cout << "GLUT:Initialize" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;

}

void Init_GLUT::idleCallback(void)
{
	glutPostRedisplay();
}

void Init_GLUT::displayCallback(void)
{
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void Init_GLUT::reshapeCallback(int width, int height)
{
	if (true == windowInformation.isReshapable)
	{
		if (listener)
		{
			listener->notifyReshape(width, height,
				windowInformation.width, windowInformation.height);
		}
		windowInformation.height = height;
		windowInformation.width = width;
	}
}

void Init_GLUT::closeCallback(void)
{
	close();
}
