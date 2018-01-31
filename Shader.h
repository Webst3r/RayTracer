#pragma once

#include<glad\glad.h>

#include "ErrorLogger.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Shader
{
public:

	GLuint program;

	Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath)
	{
		std::string vertexShaderSource;
		std::string fragmentShaderSource;

		std::ifstream vertexShaderFile(vertexShaderFilepath);
		std::ifstream fragmentShaderFile(fragmentShaderFilepath);

		std::stringstream vertexShaderSourceStream;
		std::stringstream fragmentShaderSourceStream; 

		vertexShaderSource = vertexShaderSourceStream.str();
		fragmentShaderSource = fragmentShaderSourceStream.str();

		// Create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vss = vertexShaderSource.c_str();
		GLCall(glShaderSource(vertexShader, 1, &vss, nullptr));
		GLCall(glCompileShader(vertexShader));

		// Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
		const char* fss = fragmentShaderSource.c_str();
		GLCall(glShaderSource(fragmentShader, 1, &fss, nullptr));
		GLCall(glCompileShader(fragmentShader));

		// Create shader program
		program = glCreateProgram();

		GLCall(glAttachShader(program, vertexShader));
		GLCall(glAttachShader(program, fragmentShader));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragmentShader));

	}

	void useProgram()
	{
		glUseProgram(program);
	}

private:

};