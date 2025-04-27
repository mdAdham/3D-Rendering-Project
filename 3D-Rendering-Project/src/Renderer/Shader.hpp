#pragma once
#include <string>
#include <glad/glad.h>

using namespace std;
using namespace glm;

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Init(const std::string& vertexPath, const std::string& fragmentPath);

	void use();
	unsigned int getID() const;

	void setmat4(const string& name, const mat4& mat) const;
	void setvec3(const string& name, const vec3& vec) const;
	void setfloat(const string& name, const float& val) const;
	void setint(const string& name, const int& val) const;

	unsigned int shaderID;
private:

	std::string readFile(const std::string& path);

	unsigned int compileShader(unsigned int type, const std::string& source);
};