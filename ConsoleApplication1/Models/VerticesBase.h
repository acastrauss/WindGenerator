#pragma once

#include <GL/glew.h>

#include <vector>
#include <tuple>

const std::vector<std::tuple<int, int>> componentOffsets{ std::tuple<int,int>(3,0),std::tuple<int,int>(2,3),std::tuple<int,int>(3,5) };

struct VertexWider {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat u = 0;
	GLfloat v = 0;
	GLfloat nx = 0;
	GLfloat ny = 0;
	GLfloat nz = 0;

	VertexWider(
		GLfloat x_, GLfloat y_, GLfloat z_
	);
};

class VerticesBase
{
public:
	VerticesBase() = default;
	virtual ~VerticesBase();

	GLfloat* GetVertices();
	unsigned int GetVerticesNum() const;
	unsigned int* GetIndices();
	unsigned int GetIndicesNum() const;

	static const unsigned int offset = 8; // stride
	static const unsigned int normalsOffset = 5;
protected:
	

	GLfloat* m_Vertices;
	unsigned int m_VerticesNum;
	unsigned int* m_Indices;
	unsigned int m_IndicesNum;

	virtual void InitializeVertices() = 0;
};

