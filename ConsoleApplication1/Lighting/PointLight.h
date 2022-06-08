#pragma once

#include "Lighting/Light.h"


class PointLight : public Light {
public:
	PointLight();

	PointLight(
		GLfloat red,
		GLfloat green,
		GLfloat blue,
		GLfloat aIntensity,
		GLfloat dIntensity,
		const glm::vec3& position,
		GLfloat constant,
		GLfloat linear,
		GLfloat exponent
	);

	virtual ~PointLight() = default;

	void UseLight(
		GLuint ambientIntensityLocation,
		GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation,
		GLuint positionLocation,
		GLuint constantLocation,
		GLuint linearLocation,
		GLuint exponentLocation
	);

protected:
	glm::vec3 m_Position;
	GLfloat m_Constant, m_Linear, m_Exponent;
};