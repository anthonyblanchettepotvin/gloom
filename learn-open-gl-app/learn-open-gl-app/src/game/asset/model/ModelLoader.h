#pragma once

#include <unordered_map>

#include <assimp/scene.h>

#include "../../../engine/graphics/material/Material.h"
#include "../../../engine/graphics/model/Model.h"
#include "../../../engine/graphics/texture/Texture.h"

#include "../AssetLoader.h"
#include "../shader/ShaderRegistry.h"
#include "../texture/TextureLoader.h"

class ModelLoader : public AssetLoader<Model>
{
public:
	ModelLoader(TextureLoader& textureLoader, ShaderRegistry& shaderRegistry);

	Model* Load(const std::string& path) override;

private:
	TextureLoader& m_TextureLoader;
	ShaderRegistry& m_ShaderRegistry;

	std::string m_Directory;
	std::unordered_map<std::string, Texture*> m_LoadedTextures;
	std::unordered_map<std::string, Material*> m_LoadedMaterial;

	void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	Material* LoadMaterial(aiMaterial* material);
	std::vector<Texture*> LoadMaterialTextures(aiMaterial* material, aiTextureType type);
};
