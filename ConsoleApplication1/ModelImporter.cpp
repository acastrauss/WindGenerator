#include "ModelImporter.h"
#include <iostream>


ModelImporter::ModelImporter(const std::string& texturesLocation):texturesBasePath(texturesLocation){}

void ModelImporter::ProcessNode(aiNode* node, const aiScene* scene, std::vector<int>& meshToTexMap, std::vector<Mesh>& meshes)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene,meshToTexMap,meshes);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene,meshToTexMap,meshes);
	}
}

TreeModel* ModelImporter::LoadModel(const std::string& filelocation)
{
	Assimp::Importer importer;

	std::vector<Mesh> meshes;
	std::vector<int> meshToTexMap;

	const aiScene* scene = importer.ReadFile(filelocation, 
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		std::cout << "Failed to load the scene";
		return nullptr;
	}

	ProcessNode(scene->mRootNode, scene,ref(meshToTexMap),ref(meshes));

	std::vector<Texture*> textures = LoadMaterials(scene);


	return new TreeModel(meshes, textures, meshToTexMap);

}

std::vector<Texture*> ModelImporter::LoadMaterials(const aiScene* scene)
{
	std::vector<Texture*> textures;
	int count = 0;
	for (int i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];
		count = i;

		Texture* t = LoadTexture(aiTextureType_DIFFUSE, material, &count);
		
		if (t)
		{
			textures.push_back(t);
		}
	}

	return textures;
}


Texture* ModelImporter::LoadTexture(aiTextureType type, const aiMaterial* material, int* texIndex)
{
	aiString path;

	if (material->GetTextureCount(type) == 0 || material->GetTexture(type, 0, &path) != AI_SUCCESS)
		return nullptr;

	std::string	filename = std::string(path.data);
	filename = filename.substr(filename.find_last_of('\\') + 1);
	filename = texturesBasePath + filename;
	Texture* t = nullptr;
	
	try
	{
		t = new Texture(filename.c_str());
		t->LoadTexture();

	}
	catch (std::exception)
	{
		t->ClearTexture();
		t = new Texture((texturesBasePath + "grass.png").c_str());
		t->LoadTexture();
	}

	return t;
}

void ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<int>& meshToTexMap, std::vector<Mesh>& meshes)
{

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	ProcessVertices(mesh, ref(vertices));
	ProcessIndices(mesh, ref(indices));
	
	meshToTexMap.push_back(mesh->mMaterialIndex);
	meshes.push_back(Mesh(vertices.data(), vertices.size(), indices.data(), indices.size()));
}

void ModelImporter::ProcessVertices(const aiMesh* mesh, std::vector<float>& vertices)
{
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{

		vertices.insert(vertices.end(),
			{
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z,
			});

		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(),
				{
					mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y

				});
		}
		else
		{
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}

		vertices.insert(vertices.end(),
			{
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			});
	}
}

void ModelImporter::ProcessIndices(const aiMesh* mesh, std::vector<unsigned int>& indices)
{

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
}
