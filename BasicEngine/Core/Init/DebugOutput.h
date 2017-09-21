#pragma once
#include <iostream>
#include <string>
#include <assert.h>

#include <glew\glew.h>
#include <freeglut\freeglut.h>

using namespace std;

namespace BasicEngine {
	namespace Core {
		namespace Init {
			class DebugOutput;
		}
	}
}

class BasicEngine::Core::Init::DebugOutput
{
public:
	DebugOutput() {};
	~DebugOutput() {};

	static void CALLBACK callback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar *msg,
		const void *data)
	{
		cout << "\n***********Debug Output***********"					<< endl;
		cout << "source: " << getStringForSource(source).c_str()		<< endl;
		cout << "type: " << getStringForType(type).c_str()				<< endl;
		cout << "severity: " << getStringForSeverity(severity).c_str()	<< endl;
		cout << "debug call: " << msg									<< endl;
		cout << "\n**********************************"					<< endl;
	}

private:
	static std::string getStringForType(GLenum type)
	{
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:
			return "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return "Deprecated behaviour";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return "Undefined behaviour";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			return "Performance issue";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			return "Portability issue";
			break;
		case GL_DEBUG_TYPE_MARKER:
			return "Stream annotation";
			break;
		case GL_DEBUG_TYPE_OTHER_ARB:
			return "Other";
			break;
		default:
			assert(false);
			return "";
		}
	}

	static std::string getStringForSource(GLenum source)
	{
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:
			return "API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			return "Window system";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			return "Shader compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			return "Third party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			return "Application";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			return "Other";
			break;
		default:
			assert(false);
			return "";
		}
	}

	static std::string getStringForSeverity(GLenum severity)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			return "High";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			return "Low";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			return "Notification";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			return "Medium";
			break;
		default:
			assert(false);
			return "";
		}
	}
};

