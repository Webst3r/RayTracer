#pragma once

#include "ErrorLogger.h"
#include "glad/glad.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Shader
{
public:

	GLuint shader;

    Shader(const std::string& shaderFilepath, GLenum shaderType, GLuint program)
	{
		std::stringstream shaderSourceStream; 
		std::ifstream shaderFile(shaderFilepath);
		std::string shaderSource;

		shaderSourceStream << shaderFile.rdbuf();

		shaderSource = shaderSourceStream.str();

		// Create shader
		shader = glCreateShader(shaderType);
		const char* ss = shaderSource.c_str();
		GLCall(glShaderSource(shader, 1, &ss, nullptr));
		GLCall(glCompileShader(shader));

		GLCall(glAttachShader(program, shader));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(shader));

	}
};
