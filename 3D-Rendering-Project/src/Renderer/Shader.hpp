#pragma once
#include <string>
#include <glad/glad.h>

using namespace std;
using namespace glm;

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use();
	unsigned int getID() const;

	void setmat4(const string& name, const mat4& mat) const;

private:
	unsigned int shaderID;

	std::string readFile(const std::string& path);

	unsigned int compileShader(unsigned int type, const std::string& source);
};