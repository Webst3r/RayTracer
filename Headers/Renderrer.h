#pragma once

#include <glad\glad.h>
#include <iostream>


////// OpenGL Error Checking //////
/* This should work just find across all compilers. 
	
	TODO: 
		-- Convert error codes to hex
*/

/*
	Wrap GLCall() around any OpenGL function so that said function can be cheked for errors.

	Equivalent to:
		CLClearError();
		*Some OpenGL function*
		GLLogCall();

*/
#define GLCall(x) GLClearError();\
	x;\
	GLLogCall(#x, __FILE__, __LINE__)

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "// OpenGL Error \\ (" << error << ")" << std::endl;
		return false;
	}
	return true;
}


////// OpenGL Shader Parser //////
/* 
	TODO:
		-- Take input from multiple files (vs.glsl, fs.glsl, ect...)
*/

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource parseShader(const std::string& filepath)
{
	std::fstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("#vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("#fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}
