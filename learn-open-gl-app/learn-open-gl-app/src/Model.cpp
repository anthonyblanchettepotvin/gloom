#include "Model.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(const std::string& path)
{
	LoadModel(path);
}

void Model::Draw(Shader& shader)
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	// See https://learnopengl.com/Model-Loading/Assimp for overview of Assimp's scene structure.
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;

		return;
	}

	directory = path.substr(0, path.find_last_of('\\'));

	/* Because each node (possibly) contains a set of children we want to first process
	the node in question, and then continue processing all the node's children and so on. */
	/* We could forget about processing any of the nodes and simply loop through
	all of the scene's meshes directly, without doing all this complicated stuff with recursivity.
	The reason we're doing this is that the initial idea for using nodes like this is that it
	defines a parent-child relation between meshes. */
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// Process all the node's meshes (if any)
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		/* Assimp's nodes doesn't contain the meshes themselves, but
		an index in the scene's meshes array. */
		unsigned int meshIndex = node->mMeshes[i];
		aiMesh* mesh = scene->mMeshes[meshIndex];

		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

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
;		}

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

	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		/* A material object internally stores an array of texture locations for each texture type.
		The different texture types are all prefixed with aiTextureType_.
		We use a helper function called loadMaterialTextures to retrieve, load, and initialize
		the textures from the material. */
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;

	for (size_t i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString textureRelativePath;
		material->GetTexture(type, i, &textureRelativePath);

		/* Note that we make the assumption that texture file paths in model files are local to
		the actual model object e.g. in the same directory as the location of the model itself. */
		/* Some models found over the internet use absolute paths for their texture locations,
		which won't work on each machine. In that case you probably want to manually edit the file
		to use local paths for the textures (if possible). */
		std::string textureAbsolutePath = directory + "\\" + textureRelativePath.C_Str();

		/* Loading textures is a lengthy process, so we want to avoid reloading textures that
		we already loaded. */
		bool textureAlreadyLoaded = false;
		for (size_t j = 0; j < loadedTextures.size(); j++)
		{
			if (textureAbsolutePath == loadedTextures[j].path)
			{
				textureAlreadyLoaded = true;
				textures.push_back(loadedTextures[j]);

				break;
			}
		}

		if (!textureAlreadyLoaded)
		{

			Texture texture(textureAbsolutePath, typeName);

			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
	}

	return textures;
}
