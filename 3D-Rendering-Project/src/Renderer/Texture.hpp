#pragma once

#include <filesystem>

struct Material;

class Texture
{
public:
	Texture() = default;
	//Texture(const Texture& other)
	//{
	//	m_RendererId = other.m_RendererId;
	//	m_Width = other.m_Width;
	//	m_Height = other.m_Height;
	//}//ERROR

	~Texture();

	void Load(const std::filesystem::path& path);
	void Bind();
	void Bind(unsigned int slot);
	void Unbind();

	unsigned int getId() const { return m_RendererId; }
private:
	unsigned int m_RendererId = 0;
	unsigned int m_Width = 0, m_Height = 0;

	friend Material;
};