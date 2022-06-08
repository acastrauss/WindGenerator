#include "Models/VerticesBase.h"

VertexWider::VertexWider(GLfloat x_, GLfloat y_, GLfloat z_):
	x(x_), y(y_), z(z_)
{
}

VerticesBase::~VerticesBase()
{
	if (m_Vertices) {
		delete[] m_Vertices;
	}

	if (m_Indices) {
		delete[] m_Indices;
	}
}

GLfloat* VerticesBase::GetVertices()
{
	return m_Vertices;
}

unsigned int VerticesBase::GetVerticesNum() const
{
	return m_VerticesNum;
}

unsigned int* VerticesBase::GetIndices()
{
	return m_Indices;
}

unsigned int VerticesBase::GetIndicesNum() const
{
	return m_IndicesNum;
}