#include "Models/RhombusPyramid.h"
#include <vector>
#include <Common/helpers.h>

RhombusPyramid::RhombusPyramid(const glm::vec3& baseCenter, GLfloat d1, GLfloat d2, GLfloat height):
	VerticesBase(),
	m_BaseCenter(baseCenter),
	m_D1(d1), m_D2(d2),
	m_Height(height)
{
	InitializeVertices();
}

RhombusPyramid::~RhombusPyramid()
{}


GLfloat RhombusPyramid::getSide() const
{
	return m_D1 / 2.0f;
}
GLfloat RhombusPyramid::getSlantHeight() const
{
	return sqrt(pow(m_Height, 2) - pow(m_D1 / 2.0f, 2));
}
GLfloat RhombusPyramid::getBaseHeight() const
{
	return m_D2 / 2.0f;
}

GLfloat RhombusPyramid::getD1() const
{
	return this->m_D1;
}

GLfloat RhombusPyramid::getD2() const
{
	return this->m_D2;
}

GLfloat RhombusPyramid::getHeight() const
{
	return this->m_Height;
}

GLfloat RhombusPyramid::getCoverArea() const
{
	// povrsina 4 trougla koji predstavljaju omotac piramide
	return 4 * (m_D1 * getSlantHeight() / 2);
}

void RhombusPyramid::InitializeVertices()
{
	std::vector<VertexWider> verticesV;

	//base center
	/*verticesV.push_back(
		VertexWider(
			m_BaseCenter.x,
			m_BaseCenter.y,
			m_BaseCenter.z
		)
	);*/

	// top point
	verticesV.push_back(
		VertexWider(
			m_BaseCenter.x,
			m_BaseCenter.y + m_Height,
			m_BaseCenter.z
		)
	);

	// on d1
	verticesV.push_back(
		VertexWider(
			m_BaseCenter.x,
			m_BaseCenter.y,
			m_BaseCenter.z - m_D1 / 2.0
		)
	);

	// on d1
	verticesV.push_back(
		VertexWider(
			m_BaseCenter.x,
			m_BaseCenter.y,
			m_BaseCenter.z + m_D1 / 2.0
		)
	);

	// on d2
	verticesV.push_back(
		VertexWider(
			m_BaseCenter.x - m_D2 / 2.0,
			m_BaseCenter.y,
			m_BaseCenter.z 
		)
	);
	
	// on d2
	verticesV.push_back(
		VertexWider(
			m_BaseCenter.x + m_D2 / 2.0,
			m_BaseCenter.y,
			m_BaseCenter.z 
		)
	);

	m_VerticesNum = verticesV.size() * 8;
	m_Vertices = new GLfloat[m_VerticesNum];

	// set textures
	verticesV[0].u = 0.5f;
	verticesV[0].v = 1.0f;
	
	verticesV[1].u = 0.5f;
	verticesV[1].v = 0.0f;

	verticesV[2].u = 0.5f;
	verticesV[2].v = 0.0f;

	verticesV[3].u = 0.0f;
	verticesV[3].v = 0.0f;

	verticesV[4].u = 1.0f;
	verticesV[4].v = 0.0f;


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


	// 4 triangles for wrapper + 2 for base, * 3 for each triangle
	m_IndicesNum = (4 + 2) * 3;
	m_Indices = new unsigned int[m_IndicesNum];

	m_Indices[0] = 1;
	m_Indices[1] = 2;
	m_Indices[2] = 4;
	
	m_Indices[3] = 1;
	m_Indices[4] = 3;
	m_Indices[5] = 2;
	
	m_Indices[6] = 0;
	m_Indices[7] = 2;
	m_Indices[8] = 4;

	m_Indices[9] = 0;
	m_Indices[10] = 4;
	m_Indices[11] = 1;
	
	m_Indices[12] = 0;
	m_Indices[13] = 1;
	m_Indices[14] = 3;

	m_Indices[15] = 0;
	m_Indices[16] = 3;
	m_Indices[17] = 2;

	calcAverageNormals(m_Indices, m_IndicesNum, m_Vertices, m_VerticesNum, offset, normalsOffset);

}