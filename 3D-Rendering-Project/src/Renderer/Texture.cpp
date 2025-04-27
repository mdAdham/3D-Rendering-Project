#pragma once
#include "pch.hpp"
#include "Texture.hpp"
#include "stb_image.h"

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererId);
}

void Texture::Load(const std::filesystem::path& path)
{
	stbi_set_flip_vertically_on_load(1);

	int width, height, channels;
	stbi_uc* data = nullptr;

	try
	{
		data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
	}
	catch (const std::exception& e)
	{
		std::cout << "Failed to Load Texture" << "\n";
		std::cout << e.what() << "\n";
	}

	if (data)
	{
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		glGenTextures(1, &m_RendererId);
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
		glTexStorage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_RendererId);
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererId);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
