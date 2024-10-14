#pragma once

#include <unordered_map>
#include <vector>

#include "../../../engine/object/ObjectID.h"

#include "../cubemap/GlCubemap.h"
#include "../mesh/GlMesh.h"
#include "../shader/GlShader.h"
#include "../skybox/GlSkybox.h"
#include "../sprite/GlSprite.h"
#include "../texture/GlTexture.h"
#include "../uniformbuffer/GlUniformBufferRegistry.h"

#include "GlFrame.h"
#include "GlFramebuffer.h"
#include "GlRenderbufferAttachment.h"
#include "GlTextureAttachment.h"

class Camera;
class Cubemap;
class DirectionalLight;
class GlUniformBufferRegistry;
class Mesh;
class PointLight;
class Shader;
class Skybox;
class Sprite;
class Texture;

class GlGraphicsData
{
public:
	void Initialize(size_t width, size_t height);

	void RegisterLight(const DirectionalLight& directionalLight);
	void RegisterLight(const PointLight& pointLight);

	GlFrame& GetFrame() { return m_Frame; }
	GlFramebuffer& GetFramebuffer() { return m_Framebuffer; }
	GlRenderbufferAttachment& GetRenderbufferAttachement() { return m_RenderbufferAttachment; }
	GlTextureAttachment& GetTextureAttachment() { return m_TextureAttachment; }

	GlUniformBufferRegistry& GetUniformBufferRegistry() { return m_UniformBufferRegistry; }

	std::vector<const DirectionalLight*> GetDirectionalLights() const { return m_DirectionalLights; }
	std::vector<const PointLight*> GetPointLights() const { return m_PointLights; }

	GlCubemap& GetOrCreateCubemap(const Cubemap& cubemap);
	GlMesh& GetOrCreateMesh(const Mesh& mesh);
	GlShader& GetOrCreateShader(const Shader& shader);
	GlSkybox& GetOrCreateSkybox(const Skybox& skybox);
	GlSprite& GetOrCreateSprite(const Sprite& sprite);
	GlTexture& GetOrCreateTexture(const Texture& texture);

	void UpdateUniformBuffers(const Camera& camera);
	void SendUniformBuffersToDevice();

private:
	void InitializeUniformBuffers();

	GlFrame m_Frame;
	GlFramebuffer m_Framebuffer;
	GlRenderbufferAttachment m_RenderbufferAttachment;
	GlTextureAttachment m_TextureAttachment;

	GlUniformBufferRegistry m_UniformBufferRegistry;

	std::vector<const DirectionalLight*> m_DirectionalLights;
	std::vector<const PointLight*> m_PointLights;

	std::unordered_map<ObjectID, GlCubemap> m_GlCubemaps;
	std::unordered_map<ObjectID, GlMesh> m_GlMeshes;
	std::unordered_map<ObjectID, GlShader> m_GlShaders;
	std::unordered_map<ObjectID, GlSkybox> m_GlSkyboxes;
	std::unordered_map<ObjectID, GlSprite> m_GlSprites;
	std::unordered_map<ObjectID, GlTexture> m_GlTextures;
};
