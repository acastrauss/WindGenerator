#include "Lighting/DirectionalLight.h"



DirectionalLight::DirectionalLight() :
	Light(
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f
	),
	m_Direction()
{
}

DirectionalLight::DirectionalLight(
	GLfloat red,
	GLfloat green,
	GLfloat blue,
	GLfloat aIntensity,
	GLfloat dIntensity,
	const glm::vec3& direction
) :
	Light(red, green, blue, aIntensity, dIntensity),
	m_Direction(direction)
{
}

void DirectionalLight::UseLight(
	GLuint ambientIntensityLocation,
	GLuint ambientColourLocation,
	GLuint diffuseIntensityLocation,
	GLuint diffuseDirectionLocation
)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(diffuseDirectionLocation, m_Direction.x, m_Direction.y, m_Direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}