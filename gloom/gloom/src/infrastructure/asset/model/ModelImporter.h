#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "../../../engine/asset/AssetImporter.h"

enum aiTextureType;

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

class GraphicsEngine;
class Material;
class Mesh;
class ShaderRegistry;
class Texture;
class TextureImporter;

class ModelImporter : public AssetImporter<const std::string&>
{
public:
	ModelImporter(AssetManager& assetManager, TextureImporter& textureLoader, ShaderRegistry& shaderRegistry, GraphicsEngine& graphicsEngine);

protected:
	std::unique_ptr<Object> ImportObject(const std::string& assetName, const std::string& filePath) override;

private:
	void ProcessNode(const aiNode& node, const aiScene& scene, std::vector<std::unique_ptr<Mesh>>& meshes);
	std::unique_ptr<Mesh> ProcessMesh(const aiMesh& mesh, const aiScene& scene);

	Material* ImportMaterial(const aiMaterial& material);
	std::vector<Texture*> ImportMaterialTextures(const aiMaterial& material, aiTextureType type);

	std::string GenerateTextureName(const std::string& texturePath) const;

	TextureImporter& m_TextureImporter;
	ShaderRegistry& m_ShaderRegistry;
	GraphicsEngine& m_GraphicsEngine;

	std::string m_AssetName;

	std::string m_Directory;

	std::unordered_map<std::string, Material*> m_ImportedMaterial;
	std::unordered_map<std::string, Texture*> m_ImportedTextures;
};
