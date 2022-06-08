#pragma once

#include <GL/glew.h>
#include "stb/stb_image.h"

class Texture
{
public:
	Texture(const char* fileLoc);
	~Texture();

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

private:
	GLuint m_TextureId;
	int m_Width, m_Height, m_BitDepth;
	const char* m_FileLocation;
};

