#pragma once

#include <unordered_map>

#include <assimp/scene.h>

#include "../../../game/asset/model/ModelLoader.h"
#include "../../../game/asset/shader/ShaderRegistry.h"
#include "../../../game/asset/texture/Texture.h"
#include "../../../game/asset/texture/TextureLoader.h"

class GlModelLoader : public ModelLoader
{
public:
	GlModelLoader(TextureLoader& textureLoader, ShaderRegistry& shaderRegistry);

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
