#pragma once

#include "Models/VerticesBase.h"
#include <glm/glm.hpp>

/// <summary>
/// Rhombus Pyramid for wind generator propelle
/// </summary>
class RhombusPyramid : public VerticesBase {
public:

	RhombusPyramid(
		const glm::vec3& baseCenter,
		GLfloat d1, GLfloat d2,
		GLfloat height
	);

	~RhombusPyramid();
	
	
	GLfloat getD1() const;
	GLfloat getD2() const;
	GLfloat getHeight() const;
	GLfloat getSide() const;
	GLfloat getSlantHeight() const;
	GLfloat getBaseHeight() const;
	GLfloat getCoverArea() const;



protected:
	void InitializeVertices();

private:
	RhombusPyramid() = delete;
	
	glm::vec3 m_BaseCenter;
	GLfloat m_D1, m_D2; // diagonals
	GLfloat m_Height;
};