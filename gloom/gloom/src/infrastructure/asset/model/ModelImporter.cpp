#include "ModelImporter.h"

#include <sstream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/texture.h>

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/asset/Asset.h"
#include "../../../engine/graphics/material/Material.h"
#include "../../../engine/graphics/material/MaterialAttributes.h"
#include "../../../engine/graphics/mesh/Mesh.h"
#include "../../../engine/graphics/model/Model.h"
#include "../../../engine/graphics/shader/Shader.h"
#include "../../../engine/graphics/shader/ShaderRegistry.h"
#include "../../../engine/graphics/texture/Texture.h"
#include "../../../engine/util/FileUtils.hpp"

#include "../texture/TextureImporter.h"

ModelImporter::ModelImporter(AssetManager& assetManager, TextureImporter& textureImporter, ShaderRegistry& shaderRegistry)
	: AssetImporter(assetManager), m_TextureImporter(textureImporter), m_ShaderRegistry(shaderRegistry)
{
}

std::unique_ptr<Object> ModelImporter::ImportObject(const std::string& assetName, const std::string& filePath)
{
	m_AssetName = assetName;

	Assimp::Importer importer;

	// See https://learnopengl.com/Model-Loading/Assimp for overview of Assimp's scene structure.
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		std::stringstream ss;
		ss << "Could not import model " << filePath << ".";
		gLogErrorMessage(ss.str());

		return nullptr;
	}

	m_Directory = FileUtils::ExtractDirectoryFromFilePath(filePath);

	std::vector<std::unique_ptr<Mesh>> meshes;

	/* Because each node (possibly) contains a set of children we want to first process
	the node in question, and then continue processing all the node's children and so on. */
	/* We could forget about processing any of the nodes and simply loop through
	all of the scene's meshes directly, without doing all this complicated stuff with recursivity.
	The reason we're doing this is that the initial idea for using nodes like this is that it
	defines a parent-child relation between meshes. */
	ProcessNode(*scene->mRootNode, *scene, meshes);

	return std::make_unique<Model>(meshes);
}

void ModelImporter::ProcessNode(const aiNode& node, const aiScene& scene, std::vector<std::unique_ptr<Mesh>>& meshes)
{
	// Process all the node's meshes (if any)
	for (size_t i = 0; i < node.mNumMeshes; i++)
	{
		/* Assimp's nodes doesn't contain the meshes themselves, but
		an index in the scene's meshes array. */
		unsigned int assimpMeshIndex = node.mMeshes[i];
		const aiMesh* assimpMesh = scene.mMeshes[assimpMeshIndex];

		meshes.emplace_back(ProcessMesh(*assimpMesh, scene));
	}

	for (size_t i = 0; i < node.mNumChildren; i++)
	{
		ProcessNode(*node.mChildren[i], scene, meshes);
	}
}

std::unique_ptr<Mesh> ModelImporter::ProcessMesh(const aiMesh& mesh, const aiScene& scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Process vertices
	for (size_t i = 0; i < mesh.mNumVertices; i++)
	{
		glm::vec3 position;
		position.x = mesh.mVertices[i].x;
		position.y = mesh.mVertices[i].y;
		position.z = mesh.mVertices[i].z;

		glm::vec3 normal;
		normal.x = mesh.mNormals[i].x;
		normal.y = mesh.mNormals[i].y;
		normal.z = mesh.mNormals[i].z;

		glm::vec2 textureCoordinates{ 0.0f };
		/* Assimp supports up to 8 different texture coordinates per vertex. But,
		we only care about the first set. */
		if (mesh.mTextureCoords[0])
		{
			textureCoordinates.x = mesh.mTextureCoords[0][i].x;
			textureCoordinates.y = mesh.mTextureCoords[0][i].y;
		}

		vertices.emplace_back(Vertex{ position, normal, textureCoordinates });
	}

	// Process indices
	/* Assimp's interface defines each mesh as having an array of faces,
	where each face represents a single primitive, which in our case
	(due to the aiProcess_Triangulate option) are always triangles. */
	for (size_t i = 0; i < mesh.mNumFaces; i++)
	{
		const aiFace& face = mesh.mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}

	Material* material = nullptr;

	// Process materials
	if (mesh.mMaterialIndex >= 0)
	{
		/* A material object internally stores an array of texture locations for each texture type.
		The different texture types are all prefixed with aiTextureType_.
		We use a helper function called ImportMaterialTextures to retrieve, import, and initialize
		the textures from the material. */
		const aiMaterial* assimpMaterial = scene.mMaterials[mesh.mMaterialIndex];

		material = ImportMaterial(*assimpMaterial);
	}

	return std::make_unique<Mesh>(vertices, indices, material);
}

Material* ModelImporter::ImportMaterial(const aiMaterial& material)
{
	std::string materialName = material.GetName().C_Str();

	if (m_ImportedMaterial.find(materialName) != m_ImportedMaterial.end())
	{
		return m_ImportedMaterial[materialName];
	}

	int materialShadingModel;
	material.Get(AI_MATKEY_SHADING_MODEL, materialShadingModel);

	if (materialShadingModel == aiShadingMode_Phong || materialShadingModel == aiReturn_FAILURE)
	{
		Shader& phongShader = m_ShaderRegistry.FindShader(ShadingModel::Phong);

		Material* phongMaterial = phongShader.CreateMaterialInstance();
		if (!phongMaterial)
			return nullptr;

		TextureMaterialAttribute* diffuseTexture = phongMaterial->FindAttribute<TextureMaterialAttribute>("material.texture_diffuse1");
		std::vector<Texture*> diffuseTextures = ImportMaterialTextures(material, aiTextureType_DIFFUSE);
		if (!diffuseTextures.empty())
		{
			diffuseTexture->SetValue(diffuseTextures[0]);
		}

		TextureMaterialAttribute* specularTexture = phongMaterial->FindAttribute<TextureMaterialAttribute>("material.texture_specular1");
		std::vector<Texture*> specularTextures = ImportMaterialTextures(material, aiTextureType_SPECULAR);
		if (!specularTextures.empty())
		{
			specularTexture->SetValue(specularTextures[0]);
		}

		FloatMaterialAttribute* shininess = phongMaterial->FindAttribute<FloatMaterialAttribute>("material.shininess");
		if (shininess)
		{
			shininess->SetValue(4.0f);
		}

		m_ImportedMaterial[materialName] = phongMaterial;

		return phongMaterial;
	}
	else
	{
		gLogErrorMessage("Shading model is not supported.");
	}

	return nullptr;
}

std::vector<Texture*> ModelImporter::ImportMaterialTextures(const aiMaterial& material, aiTextureType type)
{
	std::vector<Texture*> textures;

	for (size_t i = 0; i < material.GetTextureCount(type); i++)
	{
		aiString textureRelativePath;
		material.GetTexture(type, i, &textureRelativePath);

		/* Note that we make the assumption that texture file paths in model files are local to
		the actual model object e.g. in the same directory as the location of the model itself. */
		/* Some models found over the internet use absolute paths for their texture locations,
		which won't work on each machine. In that case you probably want to manually edit the file
		to use local paths for the textures (if possible). */
		std::string textureAbsolutePath = m_Directory + "\\" + textureRelativePath.C_Str();

		if (m_ImportedTextures.find(textureAbsolutePath) != m_ImportedTextures.end())
		{
			textures.emplace_back(m_ImportedTextures[textureAbsolutePath]);
		}
		else
		{
			std::string textureName = GenerateTextureName(textureAbsolutePath);

			Asset* textureAsset = m_TextureImporter.Import(textureName, textureAbsolutePath);
			if (!textureAsset)
			{
				continue;
			}

			if (Texture* texture = static_cast<Texture*>(textureAsset->GetObject()))
			{
				textures.emplace_back(texture);

				m_ImportedTextures[textureAbsolutePath] = texture;
			}
		}
	}

	return textures;
}

std::string ModelImporter::GenerateTextureName(const std::string& texturePath) const
{
	std::string textureFileName = FileUtils::ExtractFileNameFromFilePath(texturePath);
	std::string textureNameWithoutExtension = FileUtils::EraseFileExtensionFromFileName(textureFileName);
	std::string textureName = m_AssetName + "_" + textureNameWithoutExtension;

	return textureName;
}
