#include "TerrainGenerator.h"
#include <cstdio>

TerrainGenerator::TerrainGenerator(int vertexCount, float tileLength)
	:seed(rand() % 10000 + 1),size(vertexCount),widthstep(tileLength),terrain(nullptr),coordCount(coordinatesCount),
	indices(nullptr),rowoffset(coordinatesCount * vertexCount),coloffset(coordinatesCount),verticescount(vertexCount * vertexCount * coordinatesCount),
	indicescount((vertexCount-1) * (vertexCount-1) * faceindices)
{
	terrain  = new GLfloat[verticescount];
	indices = new GLuint[indicescount];

	if (!terrain || !indices)
		throw std::exception("Not enough memory to allocate the terrain");

	generateTerrain();
	generateIndices();
	generateNormals();
}

Mesh* TerrainGenerator::GetTerrainMesh() const 
{
	//std::vector<std::tuple<int,int>> componentOffsets{ std::tuple<int,int>(3,0),std::tuple<int,int>(2,3),std::tuple<int,int>(3,5) };
	Mesh* temp = new Mesh();
	temp->CreateMesh(terrain, verticescount, indices, indicescount);
	//return new Mesh(terrain, verticescount, indices, indicescount, componentOffsets, coordCount);
	return temp;
}


glm::vec3 TerrainGenerator::getNormal(float x, float z)
{
	x /= widthstep;
	z /= widthstep;

	int intX = (int)x;
	int intZ = (int)z;

	return glm::vec3(terrain[intZ * rowoffset + intX * coloffset + NX],
		terrain[intZ * rowoffset + intX * coloffset + NY],
		terrain[intZ * rowoffset + intX * coloffset + NZ]);
}


void TerrainGenerator::generateTerrain()
{
	float aggWidth = 0.0f;
	float aggHeight = 0.0f;

	for (size_t i = 0; i < size; i++)
	{
		aggWidth = 0.0f;
		for (size_t j = 0; j < size; j++)
		{
			// mesh vertex positions
			terrain[i * rowoffset + j * coloffset + X] = aggWidth;
			terrain[i * rowoffset + j * coloffset + Y] = generateHeight(aggWidth,aggHeight);
			terrain[i * rowoffset + j * coloffset + Z] = aggHeight;

			// mesh texture coordinates
			terrain[i * rowoffset + j * coloffset + U] = aggWidth;
			terrain[i * rowoffset + j * coloffset + V] = aggHeight;
			

			// place for mesh vertex normals
			terrain[i * rowoffset + j * coloffset + NX] = 0.0f;
			terrain[i * rowoffset + j * coloffset + NY] = 0.0f;
			terrain[i * rowoffset + j * coloffset + NZ] = 0.0f;

			aggWidth += widthstep;
		}
		aggHeight += widthstep;
	}
}


void TerrainGenerator::generateNormals()
{
	calcAverageNormals(indices, indicescount, terrain, verticescount, coordCount, 5);
}

void TerrainGenerator::generateIndices()
{
	int rows = size - 1;
	int cols = size - 1;

	int indicesOffset = (size - 1) * faceindices;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			indices[i * indicesOffset + j * faceindices + 0] = getIndex(j, i);
			indices[i * indicesOffset + j * faceindices + 1] = getIndex(j, i + 1);
			indices[i * indicesOffset + j * faceindices + 2] = getIndex(j + 1, i + 1);
			indices[i * indicesOffset + j * faceindices + 3] = getIndex(j + 1, i + 1);
			indices[i * indicesOffset + j * faceindices + 4] = getIndex(j + 1, i);
			indices[i * indicesOffset + j * faceindices + 5] = getIndex(j, i);
		}
	}
}


float TerrainGenerator::getRandFloat()
{
	return static_cast<float>(rand() / static_cast<float>(RAND_MAX));
}


float TerrainGenerator::getNoise(int x, int z)
{
	srand(x * 924127 + z * 52212 + seed);
	return getRandFloat() * (2.0f - 1.0f);
}


float TerrainGenerator::getSmoothNoise(int x, int z)
{
	float corners =
		(	getNoise(x - 1, z - 1) + 
			getNoise(x + 1, z - 1) + 
			getNoise(x - 1, z + 1) +
			getNoise(x + 1, z + 1)) / 16.0f;

	float sides =
		(	getNoise(x - 1, z) +
			getNoise(x + 1, z) +
			getNoise(x, z - 1) + 
			getNoise(x, z + 1)) / 8.0f;

	float center = getNoise(x, z) / 4.0f;

	return corners + sides + center;
}

float TerrainGenerator::interpolate(float a, float b, float blend)
{
	double theta = blend * PI;
	float f = (1.0f - cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

void TerrainGenerator::print()
{

	printf("\n%4s\t%19s%\t%13s\t%19s", "    ","(  X  ,  Y  ,  Z  )", "(  U  ,  V  )","( NX  , NY  , NZ  )");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("\n%4d\t(%5.3f,%5.3f,%5.3f)%\t(%5.3f,%5.3f)\t(%5.3f,%5.3f,%5.3f)",
				i*size + j,
				terrain[i * rowoffset + j * coloffset + X],
				terrain[i * rowoffset + j * coloffset + Y],
				terrain[i * rowoffset + j * coloffset + Z],
				terrain[i * rowoffset + j * coloffset + U],
				terrain[i * rowoffset + j * coloffset + V],
				terrain[i * rowoffset + j * coloffset + NX],
				terrain[i * rowoffset + j * coloffset + NY],
				terrain[i * rowoffset + j * coloffset + NZ]);
		}
	}
}

float TerrainGenerator::getInterpolatedNoise(float x, float z)
{
	int intX = (int)x;
	int intZ = (int)z;

	float fracX = x - intX;
	float fracZ = z - intZ;

	float v1 = getSmoothNoise(intX, intZ);
	float v2 = getSmoothNoise(intX + 1, intZ);
	float v3 = getSmoothNoise(intX, intZ + 1);
	float v4 = getSmoothNoise(intX + 1, intZ + 1);


	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracZ);

	return interpolate(i1, i2, fracZ);
}

int TerrainGenerator::getIndex(int x, int z)
{
	return size * z + x;
}


float TerrainGenerator::generateHeight(int x, int z)
{
	float total = getInterpolatedNoise(x / 8.0f, z / 8.0f) * heightScale;

	return total;
}


void TerrainGenerator::clear()
{
	if (this->terrain != nullptr)
	{
		delete terrain;
		terrain = nullptr;
	}

	if (this->indices != nullptr)
	{
		delete indices;
		indices = nullptr;
	}
}


TerrainGenerator::~TerrainGenerator()
{
	clear();
}