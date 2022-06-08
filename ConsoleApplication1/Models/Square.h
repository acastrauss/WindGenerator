#pragma once

#include "Models/VerticesBase.h"
#include <glm/glm.hpp>

class Square : public VerticesBase {
public:
	Square(
		const glm::vec3& center,
		GLfloat width,
		GLfloat height,
		GLfloat depth
	);

	~Square();

protected:
	void InitializeVertices();

private:

	Square() = delete;

	glm::vec3 m_Center;
	GLfloat m_Width, m_Height, m_Depth;


};
