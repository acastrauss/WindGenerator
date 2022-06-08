#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
	Mesh();
	Mesh(GLfloat* vertices,
		GLuint numOfVertices,
		GLuint* indices,
		GLuint numOfIndices);

	~Mesh() = default;

	void CreateMesh(
		GLfloat* vertices,
		GLuint numOfVertices,
		GLuint* indices,
		GLuint numOfIndices
	);

	void RenderMesh();

private:
	GLuint m_VAO, m_VBO, m_IBO, m_IndexCount;
};

