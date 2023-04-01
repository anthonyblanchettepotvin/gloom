#pragma once

#include <string>
#include <vector>

#include <assimp/mesh.h>
#include <assimp/scene.h>

#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
	Model(const std::string& path);

	void Draw(Shader& shader);

private:
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedTextures; // Used to avoid loading textures twice.
	std::string directory;

	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
};
