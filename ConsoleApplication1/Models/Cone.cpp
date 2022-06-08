#include "Models/Cone.h"

#include "Common/helpers.h"

#include <vector>

constexpr float PI = 3.14f;

Cone::Cone(const glm::vec3& center, GLfloat radius, GLfloat height, float angleInc):
	VerticesBase(),
	m_Center(center), m_Radius(radius),
	m_Height(height), m_AngleInc(PI * angleInc)
{
	InitializeVertices();
}

Cone::~Cone()
{
}

void Cone::InitializeVertices()
{
	const glm::vec3 lowerCenter = m_Center; // in xz plane
	const float lowerRadius = m_Radius;
	const float prismHeight = -m_Height;
	const glm::vec3 higherCenter(m_Center.x, m_Center.y + prismHeight, m_Center.z); // in xz plane
	const float higherRadius = m_Radius;


	std::vector<VertexWider> wrapperVertices;

	m_VerticesNum = 0;

	for (int i = 0; i < 2; i++)
	{
		auto centerToUse = i == 0 ? higherCenter : lowerCenter;
		auto radiusToUse = i == 0 ? higherRadius : lowerRadius;

		for (float j = 0; j <= 8.2 * PI; j += m_AngleInc)
		{
			VertexWider wv(
				centerToUse.x + radiusToUse * cos(j),
				centerToUse.y,
				centerToUse.z + radiusToUse * sin(j)
			);

			wrapperVertices.push_back(wv);

			m_VerticesNum++;
		}
	}

	const unsigned int verticesArrSize = wrapperVertices.size() * 8;
	m_Vertices = new GLfloat[verticesArrSize];

	for (int i = 0; i < m_VerticesNum; i++)
	{
		m_Vertices[offset * i] = wrapperVertices[i].x;
		m_Vertices[offset * i + 1] = wrapperVertices[i].y;
		m_Vertices[offset * i + 2] = wrapperVertices[i].z;
		//							next 2 values are u,v but fit well with x, y coordinates
		m_Vertices[offset * i + 3] = wrapperVertices[i].x;
		m_Vertices[offset * i + 4] = wrapperVertices[i].y;
		m_Vertices[offset * i + 5] = wrapperVertices[i].nx;
		m_Vertices[offset * i + 6] = wrapperVertices[i].ny;
		m_Vertices[offset * i + 7] = wrapperVertices[i].nz;
	}

	const unsigned int verticesPerBase = m_VerticesNum / 2;
	m_IndicesNum = verticesPerBase * 6;

	m_Indices = new unsigned int[m_IndicesNum];
	unsigned int indicesIndx = 0;


	// for every vertex in one base, there is 2 indices
	for (int i = 0; i < verticesPerBase - 1; i++)
	{
		// 6 at the time = 3 * 2
		m_Indices[indicesIndx++] = i;
		m_Indices[indicesIndx++] = verticesPerBase + i; // correspodent
		m_Indices[indicesIndx++] = verticesPerBase + i + 1; // next to correspodent
		
		m_Indices[indicesIndx++] = i;
		m_Indices[indicesIndx++] = verticesPerBase + i + 1; // next to correspodent
		m_Indices[indicesIndx++] = i + 1; // next
	}

	m_Indices[indicesIndx++] = verticesPerBase - 1;
	m_Indices[indicesIndx++] = verticesPerBase * 2 - 1; // correspodent
	m_Indices[indicesIndx++] = verticesPerBase; // next to correspodent
	
	m_Indices[indicesIndx++] = verticesPerBase - 1;
	m_Indices[indicesIndx++] = verticesPerBase; // next to correspodent
	m_Indices[indicesIndx++] = 0; // next

	calcAverageNormals(m_Indices, m_IndicesNum, m_Vertices, m_VerticesNum, offset, normalsOffset);
}
