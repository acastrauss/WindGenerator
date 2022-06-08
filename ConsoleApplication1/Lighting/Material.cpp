#include "Lighting/Material.h"

Material::Material():
	specularIntesity(0), shininess(0)
{}

Material::Material(GLfloat sIntesity, GLfloat shine):
	specularIntesity(sIntesity), shininess(shine)
{}

void Material::UseMaterial(GLuint specularIntesityLocation, GLuint shininesLocation)
{
	glUniform1f(specularIntesityLocation, specularIntesity);
	glUniform1f(shininesLocation, shininess);
}