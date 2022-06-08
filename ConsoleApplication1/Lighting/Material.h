#pragma once


#include <GL/glew.h>

class Material {
public:
	Material();
	Material(
		GLfloat sIntesity,
		GLfloat shine
	);

	~Material() = default;

	void UseMaterial(
		GLuint specularIntesityLocation,
		GLuint shininesLocation
	);

private:
	GLfloat specularIntesity;
	GLfloat shininess;
};