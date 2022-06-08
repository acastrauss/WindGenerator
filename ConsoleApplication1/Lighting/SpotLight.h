#pragma once

#include "Lighting/PointLight.h"

class SpotLight : public PointLight {

public:
	SpotLight();

	SpotLight(
		GLfloat red,
		GLfloat green,
		GLfloat blue,
		GLfloat aIntensity,
		GLfloat dIntensity,
		const glm::vec3& position,
		const glm::vec3& direction,
		GLfloat constant,
		GLfloat linear,
		GLfloat exponent,
		GLfloat edge
	);


	void UseLight(
		GLuint ambientIntensityLocation,
		GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation,
		GLuint positionLocation,
		GLuint directionLocation,
		GLuint constantLocation,
		GLuint linearLocation,
		GLuint exponentLocation,
		GLuint edgeLocation
	);

	// to set position and direction of flash
	void SetFlash(glm::vec3 pos, glm::vec3 dir);

	~SpotLight() = default;

private:

	glm::vec3 m_Direction;

	GLfloat m_Edge, m_ProcEdge;
};