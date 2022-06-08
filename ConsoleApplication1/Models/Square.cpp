#include "Models/Square.h"
#include <vector>
#include <Common/helpers.h>

Square::Square(const glm::vec3& center, GLfloat width, GLfloat height, GLfloat depth) :
	VerticesBase(),
	m_Center(center),
	m_Width(width), m_Height(height), m_Depth(depth)
{
	InitializeVertices();
}

Square::~Square()
{
}

void Square::InitializeVertices()
{
	std::vector<VertexWider> verticesV;

	glm::vec3 m_FrontTopLeft(
		m_Center.x - m_Width / 2.0,
		m_Center.y + m_Height / 2.0,
		m_Center.z + m_Depth / 2.0
	);

#pragma region VerticesAbstract

	verticesV.push_back(VertexWider(
		m_FrontTopLeft.x,
		m_FrontTopLeft.y,
		m_FrontTopLeft.z
	));
	
	verticesV.push_back(
		VertexWider(
			m_FrontTopLeft.x + m_Width,
			m_FrontTopLeft.y,
			m_FrontTopLeft.z
		)
	);

	verticesV.push_back(
		VertexWider(
			m_FrontTopLeft.x,
			m_FrontTopLeft.y - m_Height,
			m_FrontTopLeft.z
		)
	);

	verticesV.push_back(
		VertexWider(
			m_FrontTopLeft.x + m_Width,
			m_FrontTopLeft.y - m_Height,
			m_FrontTopLeft.z
		)
	);

	verticesV.push_back(
		VertexWider(
			m_FrontTopLeft.x,
			m_FrontTopLeft.y,
			m_FrontTopLeft.z - m_Depth
		)
	);

	verticesV.push_back(
		VertexWider(
			m_FrontTopLeft.x + m_Width,
			m_FrontTopLeft.y,
			m_FrontTopLeft.z - m_Depth
		)
	);

	verticesV.push_back(
		VertexWider(
			m_FrontTopLeft.x + m_Width,
			m_FrontTopLeft.y - m_Height,
			m_FrontTopLeft.z - m_Depth
		)
	);

	verticesV.push_back(
		VertexWider(
			m_FrontTopLeft.x,
			m_FrontTopLeft.y - m_Height,
			m_FrontTopLeft.z - m_Depth
		)
	);

	// fix it
	// textures
	verticesV[0].u = 0;
	verticesV[0].v = 1.0f;

	verticesV[1].u = 0.33;
	verticesV[1].v = 1.0f;

	verticesV[5].u = 0.66;
	verticesV[5].v = 1.0f;

	verticesV[4].u = 1.0;
	verticesV[4].v = 1.0f;


	verticesV[2].u = 0;
	verticesV[2].v = 0.5f;

	verticesV[3].u = 0.33;
	verticesV[3].v = 0.5f;

	verticesV[6].u = 0.66;
	verticesV[6].v = 0.5f;

	verticesV[7].u = 1.0;
	verticesV[7].v = 0.5f;


#pragma endregion


	m_VerticesNum = verticesV.size() * 8;
	m_Vertices = new GLfloat[m_VerticesNum];

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

	// number of sides * 2 (triangles) * 3 (per vertices)
	m_IndicesNum = ((verticesV.size() / 2) + 2) * 2 * 3;
	m_Indices = new unsigned int[m_IndicesNum];

	m_Indices[0] = 0;
	m_Indices[1] = 2;
	m_Indices[2] = 3;
	
	m_Indices[3] = 0;
	m_Indices[4] = 3;
	m_Indices[5] = 1;
	
	m_Indices[6] = 1;
	m_Indices[7] = 3;
	m_Indices[8] = 6;
	
	m_Indices[9] = 1;
	m_Indices[10] = 6;
	m_Indices[11] = 5;

	//
	m_Indices[12] = 5;
	m_Indices[13] = 6;
	m_Indices[14] = 7;

	m_Indices[15] = 5;
	m_Indices[16] = 7;
	m_Indices[17] = 4;

	m_Indices[18] = 4;
	m_Indices[19] = 2;
	m_Indices[20] = 7;

	m_Indices[21] = 4;
	m_Indices[22] = 2;
	m_Indices[23] = 0;

	m_Indices[24] = 4;
	m_Indices[25] = 0;
	m_Indices[26] = 1;

	m_Indices[27] = 4;
	m_Indices[28] = 1;
	m_Indices[29] = 5;

	m_Indices[30] = 7;
	m_Indices[31] = 2;
	m_Indices[32] = 3;

	m_Indices[33] = 7;
	m_Indices[34] = 3;
	m_Indices[35] = 6;

	calcAverageNormals(m_Indices, m_IndicesNum, m_Vertices, m_VerticesNum, offset, normalsOffset);
}