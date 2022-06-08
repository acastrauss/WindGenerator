#include "Lighting/SpotLight.h"

SpotLight::SpotLight():
	PointLight(),
	m_Direction(0.0f, -1.0f, 0.0f),
	m_Edge(0.0f),
	m_ProcEdge(0.0f)
{
}

SpotLight::SpotLight(
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity, 
	const glm::vec3& position, const glm::vec3& direction, 
	GLfloat constant, GLfloat linear, GLfloat exponent, 
	GLfloat edge):
	PointLight(
		red, green, blue,
		aIntensity, dIntensity,
		position, 
		constant, linear, exponent 
	),
	m_Direction(glm::normalize(direction)),
	m_Edge(edge),
	m_ProcEdge(cosf(glm::radians(edge)))
{
}

void SpotLight::UseLight(
	GLuint ambientIntensityLocation, GLuint ambientColourLocation,
	GLuint diffuseIntensityLocation, GLuint positionLocation, 
	GLuint directionLocation, GLuint constantLocation, GLuint linearLocation,
	GLuint exponentLocation, GLuint edgeLocation)
{
	PointLight::UseLight(
		ambientIntensityLocation,
		ambientColourLocation,
		diffuseIntensityLocation,
		positionLocation,
		constantLocation,
		linearLocation,
		exponentLocation
	);

	glUniform3f(
		directionLocation,
		m_Direction.x,
		m_Direction.y,
		m_Direction.z
	);

	glUniform1f(edgeLocation, m_ProcEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	m_Position = pos;
	m_Direction = dir;
}