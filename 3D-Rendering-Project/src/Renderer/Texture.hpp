#pragma once

#include <filesystem>

class Texture
{
public:
	Texture() = default;
	~Texture();

	void Load(const std::filesystem::path& path);
	void Bind();
	void Unbind();
private:
	unsigned int m_RendererId = 0;
	unsigned int m_Width = 0, m_Height = 0;
};