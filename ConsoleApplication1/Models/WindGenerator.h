#pragma once

#include "Models/Cone.h"
#include "Models/Square.h"
#include "Models/RhombusPyramid.h"
#include "Mesh2/Mesh.h"
#include "Models/Model.h"
#include "Shader/Shader.h"
#include <vector>

class WindGenerator : public Model {
public:
	WindGenerator(
		const Shader& shader, const std::vector<Texture*> textures,
		glm::vec3 baseConeCenter,
		GLfloat baseConeHeight,
		GLfloat baseConeRadius,
		GLfloat propellerD1,
		GLfloat propellerD2,
		GLfloat propellerLength
	);

	~WindGenerator();

	void Render(glm::vec3 position);
	void setDelta(float delta);
	void setRpm(GLfloat rpm);
	GLfloat getRpm() const;
	void setAngleIncrement(GLfloat increment);
	GLfloat getRotorLength() const;

	void SetBladePercentageInc(float perc);

private:
	Cone m_ConeBase;
	Square m_PropellerBase;
	RhombusPyramid m_Propeller;

	float startAngle = 0.0f;
	const float maxAngle = 360.0f;
	float angleInc = 0.5f;
	const float maxInc = 1.75f;
	const float tsr = 7.2f; // tip speed ratio
	float bladePercentageInc = 1.0f;

	float delta;

	GLfloat rpm;
	
	void CreateMeshes();

	GLfloat getPropellerSideArea() const;
};