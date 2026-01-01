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

		GLenum dataFormat = 0;
		GLint  internalFormat = 0;
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

		std::cout << "File Path: " << path << "\n";
		std::cout << "Number of Channels: " << channels << "\n";
		std::cout << "Width: " << width << "\n";
		std::cout << "Height: " << height << "\n";

		GLCMD(glGenTextures(1, &m_RendererId));
		GLCMD(glBindTexture(GL_TEXTURE_2D, m_RendererId));
		//GLCMD(glTexStorage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height));

		GLCMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GLCMD(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
		GLCMD(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data));

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to Load Texture: " << path << "\n";
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
