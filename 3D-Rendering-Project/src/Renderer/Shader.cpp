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

void Shader::setint(const string& name, const int val) const
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

GlobalShader::GlobalShader(const std::string& vertexPath, const std::string& fragmentPath)
	: Shader(vertexPath, fragmentPath)
{
	this->m_Dlight = false;
	this->m_Plight = false;
	this->m_Slight = false;

	use();

	this->setint("HasDirectionalLight", m_Dlight);
	this->setint("HasPointLight", m_Plight);
	this->setint("HasSpotLight", m_Slight);
}

void GlobalShader::InitGlobalShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	Init(vertexPath, fragmentPath);

	this->m_Dlight = false;
	this->m_Plight = false;
	this->m_Slight = false;

	use();

	this->setint("HasDirectionalLight", m_Dlight);
	this->setint("HasPointLight", m_Plight);
	this->setint("HasSpotLight", m_Slight);
}

GlobalShader::~GlobalShader()
{
	
}

void GlobalShader::SetMaterial(Material& material)
{
	use();
	this->setint("HasMaterial", 1);
	this->setfloat("material.vdiffuse", material.vdiffuse);
	this->setfloat("material.vspecular", material.vspecular);

	material.diffuse.Bind(0);
	this->setint("material.diffuse", 0);
	material.specular.Bind(1);
	this->setint("material.specular", 1);

	this->setfloat("material.shininess", material.shininess);


}

void GlobalShader::SetDirectionalLight(const DirectionalLight Dlight)
{
	use();
	this->m_Dlight = true;
	this->setint("HasDirectionalLight", m_Dlight);

	this->setvec3("directionallight.direction", Dlight.direction);
	this->setvec3("directionallight.ambient", Dlight.ambient);
	this->setvec3("directionallight.diffuse", Dlight.diffuse);
	this->setvec3("directionallight.specular", Dlight.specular);
}

void GlobalShader::SetPointLight(const array<PointLight, 32> Plight)
{
	use();
	this->m_Plight = true;
	this->setint("HasPointLight", m_Plight);
	this->setint("pointlightsize", (int)Plight.size());

	//cout << sizeof(Plight) / sizeof(PointLight) << endl;

	for (int i = 0; i < Plight.size(); i++)
	{
		string prefix("pointlights[");
		prefix += to_string(i);
		prefix += "].";
		//cout << prefix << "linear = " << Plight[i].linear << endl;

		this->setvec3(prefix + "position", Plight[i].position);

		this->setfloat(prefix + "constant", Plight[i].constant);
		this->setfloat(prefix + "linear", Plight[i].linear);
		this->setfloat(prefix + "quadratic", Plight[i].quadratic);

		this->setvec3(prefix + "ambient", Plight[i].ambient);
		this->setvec3(prefix + "diffuse", Plight[i].diffuse);
		this->setvec3(prefix + "specular", Plight[i].speclar);
	}
}

void GlobalShader::SetSpotLight(const array<SpotLight, 32> Slight)
{
	use();
	this->m_Slight = true;
	this->setint("HasSpotLight", m_Slight);
	this->setint("spotlightsize", (int)Slight.size());


	for (int i = 0; i < Slight.size(); i++)
	{
		string prefix("spotlights[");
		prefix += to_string(i);
		prefix += "].";

		this->setvec3(prefix + "position", Slight[i].position);
		this->setvec3(prefix + "direction", Slight[i].direction);

		this->setfloat(prefix + "cutOff", Slight[i].cutOff);
		this->setfloat(prefix + "outerCutOff", Slight[i].outerCutOff);

		this->setvec3(prefix + "ambient", Slight[i].ambient);
		this->setvec3(prefix + "diffuse", Slight[i].diffuse);
		this->setvec3(prefix + "specular", Slight[i].specular);

		this->setfloat(prefix + "constant", Slight[i].constant);
		this->setfloat(prefix + "linear", Slight[i].linear);
		this->setfloat(prefix + "quadratic", Slight[i].quadratic);

	}
}
