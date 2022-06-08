#pragma once

#include <cmath>
#include "Mesh2/Mesh.h"
#include "Common/helpers.h"


static const int default_terrain_size = 16;
static const int coordinatesCount = 8;
static const float heightScale = 15.0f;
static const float default_widthstep = 2.5f;
static const int faceindices = 6;
static const double PI = 3.14159265359f;

class TerrainGenerator
{
private:


	typedef enum{X = 0, Y = 1, Z = 2, U = 3, V = 4, NX = 5, NY = 6, NZ=  7} DefaultComponentsOffset;

	int size;
	int coordCount;
	float widthstep;
	int seed;

	int rowoffset;
	int coloffset;
	int verticescount;
	int indicescount;


	GLfloat* terrain;
	GLuint* indices;
	void generateTerrain();
	void generateIndices();
	void generateNormals();

	float getNoise(int x, int z);
	float getSmoothNoise(int x, int z);
	int getIndex(int x, int z);

	float interpolate(float a, float b, float blend);
	float getInterpolatedNoise(float x, float z);

	float getRandFloat();
	void clear();

public:
	Mesh* GetTerrainMesh() const;
	float generateHeight(int x, int z);
	glm::vec3 getNormal(float x, float z);
	TerrainGenerator(int vertexCount = default_terrain_size, float tileLength = default_widthstep);
	void print();


	~TerrainGenerator();

};

