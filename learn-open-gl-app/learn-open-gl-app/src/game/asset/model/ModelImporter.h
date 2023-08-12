#pragma once

#include <unordered_map>

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

class ModelImporter
{
public:
	ModelImporter(TextureImporter& textureLoader, ShaderRegistry& shaderRegistry);

	Model* Load(const std::string& path);

private:
	TextureImporter& m_TextureLoader;
	ShaderRegistry& m_ShaderRegistry;

	std::string m_Directory;
	std::unordered_map<std::string, Texture*> m_LoadedTextures;
	std::unordered_map<std::string, Material*> m_LoadedMaterial;

	void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	Material* LoadMaterial(aiMaterial* material);
	std::vector<Texture*> LoadMaterialTextures(aiMaterial* material, aiTextureType type);
};
