#pragma once
#include "pch.hpp"
#include "Drawable.hpp"

class Light : public Drawable
{
public:
	Light() = default;
	Light(const vec3& positon, const vec3& color);
	~Light();

	void Init(const vec3& positon, const vec3& color);

	void Update();
	void Render(SDL_Window* window, const mat4& view, const mat4& proj) override;

	mat4 getModelMat() const { return m_Model; };
	const vec3& getColor() const { return m_Color; };
	const vec3& getPos() const { return lightPos; };

private:

	Shader m_lightshader;

	vec3 lightPos;
	vec3 m_Color;
};

struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 speclar;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};