#pragma once

#include <vector>

class DirectionalLight;
class Mesh;
class PointLight;
class Skybox;
class Sprite;

class Scene
{
public:
	void Register(const DirectionalLight& directionalLight);
	void Register(const PointLight& pointLight);

	void Register(const Mesh& mesh);
	void Register(const Skybox& skybox);
	void Register(const Sprite& sprite);

	void Unregister(const DirectionalLight& directionalLight);
	void Unregister(const PointLight& pointLight);

	void Unregister(const Mesh& mesh);
	void Unregister(const Skybox& skybox);
	void Unregister(const Sprite& sprite);

	const std::vector<const DirectionalLight*>& GetDirectionalLights() const { return m_DirectionalLights; }
	const std::vector<const PointLight*>& GetPointLights() const { return m_PointLights; }

	const std::vector<const Mesh*>& GetMeshes() const { return m_Meshes; }
	const std::vector<const Skybox*>& GetSkyboxes() const { return m_Skyboxes; }
	const std::vector<const Sprite*>& GetSprites() const { return m_Sprites; }

private:
	std::vector<const DirectionalLight*> m_DirectionalLights;
	std::vector<const PointLight*> m_PointLights;

	std::vector<const Mesh*> m_Meshes;
	std::vector<const Skybox*> m_Skyboxes;
	std::vector<const Sprite*> m_Sprites;
};
