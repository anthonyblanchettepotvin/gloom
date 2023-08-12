#include "ModelImporter.h"

#include <iostream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/texture.h>

#include "../../../engine/graphics/material/Material.h"
#include "../../../engine/graphics/material/MaterialAttributes.h"
#include "../../../engine/graphics/model/Model.h"
#include "../../../engine/graphics/shader/Shader.h"
#include "../../../engine/graphics/texture/Texture.h"

#include "../shader/ShaderRegistry.h"
#include "../texture/TextureImporter.h"

ModelImporter::ModelImporter(TextureImporter& textureLoader, ShaderRegistry& shaderRegistry)
	: m_TextureLoader(textureLoader), m_ShaderRegistry(shaderRegistry)
{
}

Model* ModelImporter::Load(const std::string& path)
{
	Assimp::Importer importer;

	// See https://learnopengl.com/Model-Loading/Assimp for overview of Assimp's scene structure.
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;

		return nullptr;
	}

	m_Directory = path.substr(0, path.find_last_of('\\'));

	std::vector<Mesh*> meshes;

	/* Because each node (possibly) contains a set of children we want to first process
	the node in question, and then continue processing all the node's children and so on. */
	/* We could forget about processing any of the nodes and simply loop through
	all of the scene's meshes directly, without doing all this complicated stuff with recursivity.
	The reason we're doing this is that the initial idea for using nodes like this is that it
	defines a parent-child relation between meshes. */
	ProcessNode(scene->mRootNode, scene, meshes);

	return new Model(meshes);
}

void ModelImporter::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes)
{
	// Process all the node's meshes (if any)
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		/* Assimp's nodes doesn't contain the meshes themselves, but
		an index in the scene's meshes array. */
		unsigned int assimpMeshIndex = node->mMeshes[i];
		aiMesh* assimpMesh = scene->mMeshes[assimpMeshIndex];

		Mesh* mesh = ProcessMesh(assimpMesh, scene);

		meshes.push_back(mesh);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, meshes);
	}
}

Mesh* ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Process vertices
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;

		glm::vec3 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		glm::vec2 textureCoordinates(0.0f);
		/* Assimp supports up to 8 different texture coordinates per vertex. But,
		we only care about the first set. */
		if (mesh->mTextureCoords[0])
		{
			textureCoordinates.x = mesh->mTextureCoords[0][i].x;
			textureCoordinates.y = mesh->mTextureCoords[0][i].y;
		}

		Vertex vertex{ position, normal, textureCoordinates };

		vertices.push_back(vertex);
	}

	// Process indices
	/* Assimp's interface defines each mesh as having an array of faces,
	where each face represents a single primitive, which in our case
	(due to the aiProcess_Triangulate option) are always triangles. */
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Material* material = nullptr;

	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		/* A material object internally stores an array of texture locations for each texture type.
		The different texture types are all prefixed with aiTextureType_.
		We use a helper function called LoadMaterialTextures to retrieve, load, and initialize
		the textures from the material. */
		aiMaterial* assimpMaterial = scene->mMaterials[mesh->mMaterialIndex];

		material = LoadMaterial(assimpMaterial);
	}

	return new Mesh(vertices, indices, material);
}

Material* ModelImporter::LoadMaterial(aiMaterial* material)
{
	std::string materialName = material->GetName().C_Str();

	if (m_LoadedMaterial.find(materialName) != m_LoadedMaterial.end())
		return m_LoadedMaterial[materialName];

	int materialShadingModel;
	material->Get(AI_MATKEY_SHADING_MODEL, materialShadingModel);

	if (materialShadingModel == aiShadingMode_Phong || materialShadingModel == aiReturn_FAILURE)
	{
		Shader* phongShader = m_ShaderRegistry.FindShader(ShadingModel::Phong);
		if (!phongShader)
			return nullptr;

		Material* phongMaterial = phongShader->CreateMaterialInstance();
		if (!phongMaterial)
			return nullptr;

		TextureMaterialAttribute* diffuseTexture = phongMaterial->FindAttribute<TextureMaterialAttribute>("material.texture_diffuse1");
		std::vector<Texture*> diffuseTextures = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
		if (!diffuseTextures.empty())
		{
			diffuseTexture->SetValue(diffuseTextures[0]);
		}

		TextureMaterialAttribute* specularTexture = phongMaterial->FindAttribute<TextureMaterialAttribute>("material.texture_specular1");
		std::vector<Texture*> specularTextures = LoadMaterialTextures(material, aiTextureType_SPECULAR);
		if (!specularTextures.empty())
		{
			specularTexture->SetValue(specularTextures[0]);
		}

		FloatMaterialAttribute* shininess = phongMaterial->FindAttribute<FloatMaterialAttribute>("material.shininess");
		if (shininess)
		{
			shininess->SetValue(4.0f);
		}

		m_LoadedMaterial[materialName] = phongMaterial;

		return phongMaterial;
	}
	else
	{
		std::cerr << "Unsupported shading model" << std::endl;
	}

	return nullptr;
}

std::vector<Texture*> ModelImporter::LoadMaterialTextures(aiMaterial* material, aiTextureType type)
{
	std::vector<Texture*> textures;

	for (size_t i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString textureRelativePath;
		material->GetTexture(type, i, &textureRelativePath);

		/* Note that we make the assumption that texture file paths in model files are local to
		the actual model object e.g. in the same directory as the location of the model itself. */
		/* Some models found over the internet use absolute paths for their texture locations,
		which won't work on each machine. In that case you probably want to manually edit the file
		to use local paths for the textures (if possible). */
		std::string textureAbsolutePath = m_Directory + "\\" + textureRelativePath.C_Str();

		if (m_LoadedTextures.find(textureAbsolutePath) != m_LoadedTextures.end())
		{
			textures.push_back(m_LoadedTextures[textureAbsolutePath]);
		}
		else
		{
			Texture* texture = m_TextureLoader.Load(textureAbsolutePath);

			textures.push_back(texture);

			m_LoadedTextures[textureAbsolutePath] = texture;
		}
	}

	return textures;
}
