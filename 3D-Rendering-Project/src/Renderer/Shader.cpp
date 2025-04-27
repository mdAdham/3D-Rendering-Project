#include "pch.hpp"
#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace glm;

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);

	glLinkProgram(shaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(shaderID);
}

void Shader::Init(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);

	glLinkProgram(shaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(shaderID);
}

unsigned int Shader::getID() const
{
	return shaderID;
}

void Shader::setmat4(const string& name, const mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, value_ptr(mat));
}

void Shader::setvec3(const string& name, const vec3& vec) const
{
	glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, value_ptr(vec));
}

void Shader::setfloat(const string& name, const float& val) const
{
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), val);
}

void Shader::setint(const string& name, const int& val) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), val);
}

std::string Shader::readFile(const std::string& path)
{
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];

		glGetShaderInfoLog(shader, 512, nullptr, infoLog);

		std::cerr << "Error: Shader Compilation Failed\n" << infoLog << std::endl;
	}

	return shader;
}
