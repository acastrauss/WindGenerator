#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
	Light();
	Light(
		GLfloat red,
		GLfloat green,
		GLfloat blue,
		GLfloat aIntensity,
		GLfloat dIntensity
	);
	virtual ~Light() = default;

	/*virtual void UseLight(
		GLuint ambientIntensityLocation,
		GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation
	) = 0;*/

protected:
	glm::vec3 colour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};