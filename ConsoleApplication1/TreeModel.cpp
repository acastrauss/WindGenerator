#include "TreeModel.h"
#include <glm/gtc/type_ptr.hpp>

TreeModel::TreeModel(std::vector<Mesh>& meshes, std::vector<Texture*> textures, std::vector<int>& meshTextureMap) :
	Model(meshes, textures, meshTextureMap) {}



void TreeModel::Render(glm::vec3 position)
{
	m_ModelMatrix = glm::mat4(1.0f);
	m_ModelMatrix = glm::translate(m_ModelMatrix, position);
	m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.5, 0.5, 0.5));

	glUniformMatrix4fv(m_Shader.GetUniformLocations().ModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
	
	for (int i = 0; i < m_Meshes.size(); i++)
	{
		int materialIndex = meshToTextureMap[i];

		if (materialIndex < m_Textures.size())
		{
			m_Textures[i]->UseTexture();
		}

		m_Meshes[i].RenderMesh();
	}
}

void TreeModel::CreateMeshes()
{
	
}

void TreeModel::SetShader(Shader& shader)
{
	this->m_Shader = shader;
}