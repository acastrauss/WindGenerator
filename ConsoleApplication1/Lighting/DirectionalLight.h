#pragma once


#include "Lighting/Light.h"

class DirectionalLight : public Light {

public:
	DirectionalLight();
	~DirectionalLight() = default;

	DirectionalLight(
		GLfloat red,
		GLfloat green,
		GLfloat blue,
		GLfloat aIntensity,
		GLfloat dIntensity,
		const glm::vec3& direction
	);
	
	void UseLight(
		GLuint ambientIntensityLocation,
		GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation,
		GLuint diffuseDirectionLocation
	);

private:
	glm::vec3 m_Direction;

};