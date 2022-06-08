#include "helpers.h"

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int vertexCount, unsigned int vLength, unsigned int normalsOffset)
{
	GLfloat* normalsAtIndex = nullptr;
	GLint triangleIndex0, triangleIndex1, triangleIndex2;


	for (size_t i = 0; i < indiceCount; i += 3)
	{
		triangleIndex0 = indices[i] * vLength;
		triangleIndex1 = indices[i + 1] * vLength;
		triangleIndex2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[triangleIndex1] - vertices[triangleIndex0],
			vertices[triangleIndex1 + 1] - vertices[triangleIndex0 + 1],
			vertices[triangleIndex1 + 2] - vertices[triangleIndex0 + 2]);

		glm::vec3 v2(vertices[triangleIndex2] - vertices[triangleIndex0],
			vertices[triangleIndex2 + 1] - vertices[triangleIndex0 + 1],
			vertices[triangleIndex2 + 2] - vertices[triangleIndex0 + 2]);

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
		if (isnan(normal.x))
			continue;

		triangleIndex0 += normalsOffset;
		triangleIndex1 += normalsOffset;
		triangleIndex2 += normalsOffset;

		vertices[triangleIndex0] += normal.x;
		vertices[triangleIndex0 + 1] += normal.y;
		vertices[triangleIndex0 + 2] += normal.z;

		vertices[triangleIndex1] += normal.x;
		vertices[triangleIndex1 + 1] += normal.y;
		vertices[triangleIndex1 + 2] += normal.z;

		vertices[triangleIndex2] += normal.x;
		vertices[triangleIndex2 + 1] += normal.y;
		vertices[triangleIndex2 + 2] += normal.z;
	}


	for (size_t i = 0; i < vertexCount / vLength; i++)
	{
		unsigned int offset = i * vLength + normalsOffset;

		glm::vec3 normal(vertices[offset], vertices[offset + 1], vertices[offset + 2]);
		normal = glm::normalize(normal);

		vertices[offset] = normal.x;
		vertices[offset + 1] = normal.y;
		vertices[offset + 2] = normal.z;
	}
}

std::vector<std::tuple<float, float>> CalculatePower(float wind_velocity, float blade_length)
{
	float air_density = 1.3f;
	float Cp = 0.4f;

	std::vector<std::tuple<float, float>> active_reactivePower;
	
	float activePower = 1 / 2.0f * air_density * pow(blade_length, 2) * 3.14 * pow(wind_velocity, 3) * Cp;
	
	active_reactivePower.push_back(std::tuple<float, float>{activePower, 0.05f * activePower});
	
	return active_reactivePower;
}