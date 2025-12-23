#pragma once
#include <string>
#include <array>

#include <glad/glad.h>
#include "Texture.hpp"
#include "AllLight.hpp"


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

struct Material
{
	float vdiffuse = 0.f;
	float vspecular = 0.f;

	Texture diffuse;
	Texture specular;

	float shininess = 0.f;
};

// GlobalShader Class Uses "FullShader.frag and FullShader.vert" SHIT!!

class GlobalShader : public Shader
{
public:
	/// <summary>
	/// Pass the File path of the "FullShader.frag" and "FullShader.vert" Please...
	/// </summary>
	/// <param name="vertexPath">Vertex Shader File Path</param>
	/// <param name="fragmentPath">Fragment Shader File Path</param>
	GlobalShader() = default;
	GlobalShader(const std::string& vertexPath, const std::string& fragmentPath);

	void InitGlobalShader(const std::string& vertexPath, const std::string& fragmentPath);

	~GlobalShader();

	void SetMaterial(Material material);
	void SetDirectionalLight(const DirectionalLight Dlight);
	void SetPointLight(const std::array<PointLight, 32> Plight);
	void SetSpotLight(const std::array<SpotLight, 32> Slight);

private:
	bool m_Dlight = false;
	bool m_Plight = false;
	bool m_Slight = false;
};