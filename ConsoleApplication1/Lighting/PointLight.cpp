#include "Lighting/PointLight.h"

PointLight::PointLight():
	Light(),
	m_Position(),
	m_Constant(1.0f),
	m_Linear(0),
	m_Exponent(0)
{}

PointLight::PointLight(
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	const glm::vec3& position,
	GLfloat constant, GLfloat linear, GLfloat exponent):
	Light(red, green, blue, aIntensity, dIntensity),
	m_Position(position),
	m_Constant(constant), m_Linear(linear), m_Exponent(exponent)
{
}

void PointLight::UseLight(
	GLuint ambientIntensityLocation, 
	GLuint ambientColourLocation,
	GLuint diffuseIntensityLocation,
	GLuint positionLocation,
	GLuint constantLocation,
	GLuint linearLocation,
	GLuint exponentLocation
)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform3f(positionLocation, m_Position.x, m_Position.y, m_Position.z);

	glUniform1f(constantLocation, m_Constant);
	glUniform1f(linearLocation, m_Linear);
	glUniform1f(exponentLocation, m_Exponent);
}