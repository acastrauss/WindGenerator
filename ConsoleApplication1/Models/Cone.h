#pragma once

#include <Models/VerticesBase.h>
#include <glm/glm.hpp>

constexpr float defaultAngleInc = 1.0f / 6.0f;

class Cone : public VerticesBase
{
public:
	Cone(
		const glm::vec3& center,
		GLfloat radius,
		GLfloat height,
		float angleInc = defaultAngleInc
	);

	~Cone();

protected:
	void InitializeVertices();

private:

	Cone() = delete;

	glm::vec3 m_Center;
	GLfloat m_Radius;
	GLfloat m_Height;
	float m_AngleInc;

};

