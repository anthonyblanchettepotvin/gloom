#pragma once

#include <string>
#include <unordered_map>

#include "../../../engine/asset/AssetImporter.h"

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

enum aiTextureType;

class Material;
class Mesh;
class Model;
class ShaderRegistry;
class Texture;
class TextureImporter;

class ModelImporter : public AssetImporter<const std::string&>
{
public:
	ModelImporter(AssetManager& assetManager, TextureImporter& textureLoader, ShaderRegistry& shaderRegistry);

protected:
	std::unique_ptr<ObjectBase> ImportObject(const std::string& filePath) override;

private:
	TextureImporter& m_TextureImporter;
	ShaderRegistry& m_ShaderRegistry;

	std::string m_Directory;
	std::unordered_map<std::string, Texture*> m_ImportedTextures;
	std::unordered_map<std::string, Material*> m_ImportedMaterial;

	void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	Material* ImportMaterial(aiMaterial* material);
	std::vector<Texture*> ImportMaterialTextures(aiMaterial* material, aiTextureType type);
};
