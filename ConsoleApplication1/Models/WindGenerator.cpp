#include "Models/WindGenerator.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

WindGenerator::WindGenerator(
	const Shader& shader, const std::vector<Texture*> textures,
	glm::vec3 baseConeCenter,
	GLfloat baseConeHeight, GLfloat baseConeRadius,
	GLfloat propellerD1, GLfloat propellerD2,
	GLfloat propellerLength,
	WindSpeedData* wsdPtr) :
	Model(shader, textures),
	m_ConeBase(
		baseConeCenter, baseConeRadius, baseConeHeight
	),
	m_PropellerBase(
		glm::vec3(baseConeCenter.x, baseConeCenter.y, baseConeCenter.z),
		0.15f, 0.45f, 0.3f
	),
	m_Propeller(
		glm::vec3(baseConeCenter.x, baseConeCenter.y, baseConeCenter.z + 0.2f),
		propellerD1, propellerD2, propellerLength
	),
	m_WSDPtr(wsdPtr)
{
	CreateMeshes();
}

void WindGenerator::setAngleIncrement(GLfloat increment)
{
	this->angleInc = increment;
}

void WindGenerator::setDelta(float delta)
{
	this->delta = delta;
}

GLfloat WindGenerator::getRotorLength() const
{
	return m_Propeller.getHeight();
}

GLfloat WindGenerator::getPropellerSideArea() const
{
	return 0.0f;
}

void WindGenerator::SetBladePercentageInc(float perc)
{
	bladePercentageInc = perc;
}

WindGenerator::~WindGenerator()
{
}

void WindGenerator::CreateMeshes()
{
	Mesh meshCone;
	meshCone.CreateMesh(
		m_ConeBase.GetVertices(), m_ConeBase.GetVerticesNum(),
		m_ConeBase.GetIndices(), m_ConeBase.GetIndicesNum()
	);

	m_Meshes.push_back(meshCone);

	Mesh meshSquare;
	meshSquare.CreateMesh(
		m_PropellerBase.GetVertices(), m_PropellerBase.GetVerticesNum(),
		m_PropellerBase.GetIndices(), m_PropellerBase.GetIndicesNum()
	);
	m_Meshes.push_back(meshSquare);

	Mesh meshPropeller;
	meshPropeller.CreateMesh(
		m_Propeller.GetVertices(), m_Propeller.GetVerticesNum(),
		m_Propeller.GetIndices(), m_Propeller.GetIndicesNum()
	);
	m_Meshes.push_back(meshPropeller);
}

void WindGenerator::Render(glm::vec3 position)
{
	bool rotate = m_WSDPtr->WindSpeed >= MinWindSpeedToRotate && m_WSDPtr->WindSpeed <= MaxWindSpeedToRotate;

	m_ModelMatrix = glm::mat4(1.0f);
	
	glm::vec3 scaledPosition = position;
	scaledPosition.y += (bladePercentageInc - 1.0f) * 7.0f;

	m_ModelMatrix = glm::translate(m_ModelMatrix, scaledPosition);

	m_ModelMatrix = glm::scale(
		m_ModelMatrix,
		glm::vec3(bladePercentageInc, bladePercentageInc, bladePercentageInc)
	);

	glUniformMatrix4fv(
		m_UniformLocation.ModelMatrixLocation,
		1,
		GL_FALSE,
		glm::value_ptr(m_ModelMatrix)
	);

	m_Meshes[0].RenderMesh(); // cone base
	
	m_Meshes[1].RenderMesh(); // propeller base

	// first propeller
	m_ModelMatrix = glm::mat4(1.0f);

	m_ModelMatrix = glm::translate(m_ModelMatrix, scaledPosition);

	m_ModelMatrix = glm::rotate(
		m_ModelMatrix,
		glm::radians(rotate ? startAngle : 0.0f),
		glm::vec3(0, 0, 1)
	);
	
	m_ModelMatrix = glm::scale(
		m_ModelMatrix,
		glm::vec3(bladePercentageInc, bladePercentageInc, bladePercentageInc)
	);

	glUniformMatrix4fv(
		m_UniformLocation.ModelMatrixLocation,
		1,
		GL_FALSE,
		glm::value_ptr(m_ModelMatrix)
	);

	m_Meshes[2].RenderMesh();

	// second propeller
	m_ModelMatrix = glm::mat4(1.0f);

	m_ModelMatrix = glm::translate(m_ModelMatrix, scaledPosition);

	m_ModelMatrix = glm::rotate(
		m_ModelMatrix,
		glm::radians(rotate ? (startAngle + 120.0f) : 120.0f),
		glm::vec3(0, 0, 1)
	);

	m_ModelMatrix = glm::scale(
		m_ModelMatrix,
		glm::vec3(bladePercentageInc, bladePercentageInc, bladePercentageInc)
	);
	
	glUniformMatrix4fv(
		m_UniformLocation.ModelMatrixLocation,
		1,
		GL_FALSE,
		glm::value_ptr(m_ModelMatrix)
	);

	m_Meshes[2].RenderMesh();

	// third propeller
	m_ModelMatrix = glm::mat4(1.0f);

	m_ModelMatrix = glm::translate(m_ModelMatrix, scaledPosition);
	
	m_ModelMatrix = glm::rotate(
		m_ModelMatrix,
		glm::radians(rotate ? (startAngle + 240.0f) : 240.0f),
		glm::vec3(0, 0, 1)
	);

	m_ModelMatrix = glm::scale(
		m_ModelMatrix,
		glm::vec3(bladePercentageInc, bladePercentageInc, bladePercentageInc)
	);

	glUniformMatrix4fv(
		m_UniformLocation.ModelMatrixLocation,
		1,
		GL_FALSE,
		glm::value_ptr(m_ModelMatrix)
	);

	m_Meshes[2].RenderMesh();

	if (rotate) {
		startAngle += angleInc * delta;
	}
}
