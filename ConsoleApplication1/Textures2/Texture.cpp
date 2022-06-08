#include "Textures2/Texture.h"

#include "stb/stb_image.h"

Texture::Texture(const char* fileLoc):
	m_TextureId(0),
	m_Width(0),
	m_Height(0),
	m_BitDepth(0),
	m_FileLocation(fileLoc)
{
}

Texture::~Texture()
{
	ClearTexture();
}

void Texture::LoadTexture()
{
	unsigned char* texData =
		stbi_load(
			m_FileLocation, &m_Width, &m_Height, &m_BitDepth, 0
		);

	if (!texData)
	{
		throw "Failed to find texture!";
	}

	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	GLenum const fmt[] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glTexImage2D(
		GL_TEXTURE_2D, 0, fmt[m_BitDepth - 1], m_Width, m_Height,
		0, fmt[m_BitDepth - 1], GL_UNSIGNED_BYTE, texData
	);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &m_TextureId);
	m_TextureId = 0;
	m_Width = 0;
	m_Height = 0;
	m_BitDepth = 0;
	m_FileLocation = NULL;
}
