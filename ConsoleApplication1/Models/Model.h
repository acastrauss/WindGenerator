#pragma once

#include <glm/glm.hpp>
#include <Shader/Shader.h>
#include <Textures2/Texture.h>
#include <Mesh2/Mesh.h>

#include <vector>

class Model {

public:
	Model(
		const Shader& shader,
		const std::vector<Texture*> textures = {}
	);

	Model(std::vector<Mesh>& meshes, std::vector<Texture*> textures, std::vector<int>& meshTextureMap);
	virtual ~Model();

	virtual void Render(glm::vec3 position) = 0;
	
	virtual void SetProjectionMatrix(const glm::mat4& proj);
	virtual void SetViewMatrix(const glm::mat4& view);
	virtual void SetModelMatrix(const glm::mat4& model);

	virtual void SetUniformLocations(const UniformLocations& uniLocs);
	void AddMesh(Mesh mesh);
	void AddTexture(Texture* texture);
protected:

	std::vector<Mesh> m_Meshes;
	std::vector<int> meshToTextureMap;

	Shader m_Shader;
	UniformLocations m_UniformLocation;
	std::vector<Texture*> m_Textures;

	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ModelMatrix;

	virtual void CreateMeshes() = 0;
};