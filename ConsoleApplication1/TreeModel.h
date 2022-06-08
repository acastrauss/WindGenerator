#pragma once

#include <Models/Model.h>

class TreeModel : public Model
{
public:
	TreeModel();
	TreeModel(std::vector<Mesh>& meshes, std::vector<Texture*> textures, std::vector<int>& meshTextureMap);
	void Render(glm::vec3 position);
	void CreateMeshes();

	void SetShader(Shader& shader);

};

