#pragma once

#include "Models/VerticesBase.h"
#include <glm/glm.hpp>


class GrassQuad : public VerticesBase {
public:
	GrassQuad(
		glm::vec3 bottomCenter,
		GLfloat width,
		GLfloat height
	);
	~GrassQuad();

	void InitializeVertices();

private:
	glm::vec3 m_BottomCenter;
	GLfloat m_Width;
	GLfloat m_Height;
};