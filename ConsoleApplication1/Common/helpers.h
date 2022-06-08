#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <tuple>

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int vertexCount, unsigned int vLength, unsigned int normalsOffset);
std::vector<std::tuple<float,float>> CalculatePower(float wind_velocity, float blade_length);