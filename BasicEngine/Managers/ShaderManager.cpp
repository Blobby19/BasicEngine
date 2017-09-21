#include "ShaderManager.h"

using namespace BasicEngine;

std::map<std::string, GLuint> Managers::ShaderManager::programs;

Managers::ShaderManager::ShaderManager(){}
Managers::ShaderManager::~ShaderManager()
{
	std::map<std::string, GLuint>::iterator it;
	for (it = programs.begin(); it != programs.end(); ++it)
	{
		GLuint pr = it->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}

std::string Managers::ShaderManager::readShader(const std::string &filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file " << filename.c_str() << std::endl;
		terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint Managers::ShaderManager::createShader(GLenum shaderType,
	const std::string &source,
	const std::string &shaderName)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check errors
	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}

	return shader;
}

void Managers::ShaderManager::createProgram(const std::string &shaderName,
	const std::string &vertexShaderFilename,
	const std::string &fragmentShaderFilename)
{
	//read the shader files and save the code
	std::string vertex_shader_code = readShader(vertexShaderFilename);
	std::string fragment_shader_code = readShader(fragmentShaderFilename);

	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	//check for link errors
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "ShaderLoader: LINK ERROR" << std::endl << &program_log[0] << std::endl;

		return;
	}

	programs[shaderName] = program;
}

const GLuint Managers::ShaderManager::getShader(const std::string &shaderName)
{
	return programs.at(shaderName);
}