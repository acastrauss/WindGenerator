#include "Mesh2/Mesh.h"

#include "glm/glm.hpp"
#include <iostream>

Mesh::Mesh():
	m_VAO(0),
	m_VBO(0),
	m_IBO(0),
	m_IndexCount(0)
{
}

void Mesh::CreateMesh(
	GLfloat* vertices, GLuint numOfVertices,
	GLuint* indices, GLuint numOfIndices)
{
	m_IndexCount = numOfIndices;

	{
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		{
			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				numOfIndices * sizeof(indices[0]),
				indices,
				GL_STATIC_DRAW
			);
		}

		{
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(
				GL_ARRAY_BUFFER,
				numOfVertices * sizeof(vertices[0]),
				vertices,
				GL_STATIC_DRAW
			);
		}

		static const GLuint nOfVertices = 3;
		static const GLuint nOfTexture = 2;
		static const GLuint nOfNormal = 3;
		static const GLuint textureOffset = nOfVertices;
		static const GLuint normalUffset = textureOffset + nOfTexture;

		// vertices
		glVertexAttribPointer(
			0, nOfVertices, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0
		);
		glEnableVertexAttribArray(0);

		// texture (last param offset by 3)
		glVertexAttribPointer(
			1, nOfTexture, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * textureOffset)
		);
		glEnableVertexAttribArray(1);

		// normals
		glVertexAttribPointer(
			2, nOfNormal, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * normalUffset)
		);
		glEnableVertexAttribArray(2);

		// reset buffer binding
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Mesh::RenderMesh()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glDrawElements(
		GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0
	);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(GLfloat* vertices,
	GLuint numOfVertices,
	GLuint* indices,
	GLuint numOfIndices)
{
	CreateMesh(vertices, numOfVertices, indices, numOfIndices);
}
