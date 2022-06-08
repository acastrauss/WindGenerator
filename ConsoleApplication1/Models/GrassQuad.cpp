#include "Models/GrassQuad.h"
#include <vector>
#include <Common/helpers.h>

GrassQuad::GrassQuad(glm::vec3 bottomCenter, GLfloat width, GLfloat height):
	VerticesBase(),
	m_BottomCenter(bottomCenter),
	m_Width(width),
	m_Height(height)
{
	InitializeVertices();
}

GrassQuad::~GrassQuad()
{
}

void GrassQuad::InitializeVertices()
{
	std::vector<VertexWider> verticesV;

	auto m_TopLeft = m_BottomCenter;
	m_TopLeft.x -= m_Width / 2.0;
	m_TopLeft.y += m_Height;

	// top left
	verticesV.push_back(
		VertexWider(
			m_TopLeft.x,
			m_TopLeft.y,
			m_TopLeft.z
		)
	);
	
	verticesV[0].u = 0.0f;
	verticesV[0].v = 1.0f;

	verticesV.push_back(
		VertexWider(
			m_TopLeft.x + m_Width,
			m_TopLeft.y,
			m_TopLeft.z 
		)
	);

	verticesV[1].u = 1.0f;
	verticesV[1].v = 1.0f;
	
	verticesV.push_back(
		VertexWider(
			m_TopLeft.x + m_Width,
			m_TopLeft.y + m_Height,
			m_TopLeft.z
		)
	);

	verticesV[2].u = 1.0f;
	verticesV[2].v = 0.0f;

	verticesV.push_back(
		VertexWider(
			m_TopLeft.x,
			m_TopLeft.y + m_Height,
			m_TopLeft.z
		)
	);

	verticesV[3].u = 0.0f;
	verticesV[3].v = 0.0f;

	m_Vertices = new GLfloat[verticesV.size() * 8];
	m_VerticesNum = verticesV.size() * 8;

	for (int i = 0; i < verticesV.size(); i++)
	{
		m_Vertices[offset * i] = verticesV[i].x;
		m_Vertices[offset * i + 1] = verticesV[i].y;
		m_Vertices[offset * i + 2] = verticesV[i].z;
		m_Vertices[offset * i + 3] = verticesV[i].u;
		m_Vertices[offset * i + 4] = verticesV[i].v;
		m_Vertices[offset * i + 5] = verticesV[i].nx;
		m_Vertices[offset * i + 6] = verticesV[i].ny;
		m_Vertices[offset * i + 7] = verticesV[i].nz;
	}

	// 2 triangle * 3 vertices
	m_IndicesNum = 2 * 3;
	m_Indices = new unsigned int[m_IndicesNum];

	m_Indices[0] = 0;
	m_Indices[1] = 2;
	m_Indices[2] = 3;

	m_Indices[3] = 0;
	m_Indices[4] = 1;
	m_Indices[5] = 2;

	calcAverageNormals(m_Indices, m_IndicesNum, m_Vertices, m_VerticesNum, offset, normalsOffset);
}