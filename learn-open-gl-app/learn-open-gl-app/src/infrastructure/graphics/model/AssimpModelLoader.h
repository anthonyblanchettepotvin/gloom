#pragma once

#include <unordered_map>

#include "../../../engine/graphics/model/ModelLoader.h"

class AssimpModelLoader : public ModelLoader
{
public:
	Model* Load(const std::string& path) override;

private:
	std::string directory;
	std::unordered_map<std::string, Texture*> loadedTextures;
	std::unordered_map<std::string, Material*> loadedMaterial;

	void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	Material* LoadMaterial(aiMaterial* material);
	std::vector<Texture*> LoadMaterialTextures(aiMaterial* material, aiTextureType type);

	TextureType aiTextureTypeToTextureType(aiTextureType type) const;
};
