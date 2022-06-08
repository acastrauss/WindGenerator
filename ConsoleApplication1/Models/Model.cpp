#include "Models/Model.h"
#include <glm/ext/matrix_clip_space.hpp>

Model::Model(const Shader& shader, std::vector<Texture*> textures):
	m_Meshes(),
	m_Shader(shader),
	m_UniformLocation(),
	m_Textures(textures),
	m_ProjectionMatrix(1.0f),
	m_ViewMatrix(1.0f),
	m_ModelMatrix(1.0f)
{
}

Model::~Model()
{
}

Model::Model(std::vector<Mesh>& meshes, std::vector<Texture*> textures, std::vector<int>& meshTextureMap)
{

	for (int i = 0; i < meshes.size(); i++)
		m_Meshes.push_back(meshes[i]);

	for (int i = 0; i < textures.size(); i++)
		m_Textures.push_back(textures[i]);

	for (int i = 0; i < meshTextureMap.size(); i++)
		this->meshToTextureMap.push_back(meshTextureMap[i]);
}

void Model::SetProjectionMatrix(const glm::mat4& proj)
{
	m_ProjectionMatrix = proj;
}

void Model::AddMesh(Mesh mesh)
{
	m_Meshes.push_back(mesh);
}

void Model::AddTexture(Texture* texture)
{
	m_Textures.push_back(texture);
}

void Model::SetViewMatrix(const glm::mat4& view)
{
	m_ViewMatrix = view;
}

void Model::SetModelMatrix(const glm::mat4& model)
{
	m_ModelMatrix = model;
}

void Model::SetUniformLocations(const UniformLocations& uniLocs)
{
	m_UniformLocation = uniLocs;
}