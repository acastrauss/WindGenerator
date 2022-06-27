#pragma once

#include "Models/Cone.h"
#include "Models/Square.h"
#include "Models/RhombusPyramid.h"
#include "Mesh2/Mesh.h"
#include "Models/Model.h"
#include "Shader/Shader.h"
#include <vector>
#include "UIComponents/WindSpeedData.h"

constexpr static float MinWindSpeedToRotate = 4.0f;
constexpr static float MaxWindSpeedToRotate = 24.0f;

class WindGenerator : public Model {
public:
	WindGenerator(
		const Shader& shader, const std::vector<Texture*> textures,
		glm::vec3 baseConeCenter,
		GLfloat baseConeHeight,
		GLfloat baseConeRadius,
		GLfloat propellerD1,
		GLfloat propellerD2,
		GLfloat propellerLength,
		WindSpeedData* wsdPtr
	);

	~WindGenerator();

	void Render(glm::vec3 position);
	void setDelta(float delta);
	void setAngleIncrement(GLfloat increment);
	GLfloat getRotorLength() const;

	void SetBladePercentageInc(float perc);

private:
	Cone m_ConeBase;
	Square m_PropellerBase;
	RhombusPyramid m_Propeller;
	WindSpeedData* m_WSDPtr;

	float startAngle = 0.0f;
	const float maxAngle = 360.0f;
	float angleInc = 0.5f;
	const float maxInc = 1.75f;
	const float tsr = 7.2f; // tip speed ratio
	float bladePercentageInc = 1.0f;

	float delta;

	
	void CreateMeshes();

	GLfloat getPropellerSideArea() const;

	bool rotate = true;
	const unsigned int framesToStop = 500;
	/// <summary>
	/// Frames since rotation should stop
	/// </summary>
	unsigned int framesRotationOffCnt = 0;
	float rotationStoppedAngle = 0.0f;
	float baseModulate = 10.0f;

};