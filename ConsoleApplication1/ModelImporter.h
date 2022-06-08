#pragma once


#include <Models/Model.h>
#include "TreeModel.h"
#include <Textures2/Texture.h>
#include <string>


#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>


class ModelImporter
{
public:
	ModelImporter(const std::string& texturesLocation);
	TreeModel* LoadModel(const std::string& modellocation);

private:


	const std::string texturesBasePath;

	void ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<int>& meshToTexMap,std::vector<Mesh>& meshes);
	void ProcessNode(aiNode* node, const aiScene* scene, std::vector<int>& meshToTexMap,std::vector<Mesh>&meshes);
	std::vector<Texture*> LoadMaterials(const aiScene* scene);
	Texture* LoadTexture(aiTextureType type, const aiMaterial* material, int* texIndex);
	void ProcessVertices(const aiMesh* mesh, std::vector<float>& vertices);
	void ProcessIndices(const aiMesh* mesh, std::vector<unsigned int>& indices);
};

