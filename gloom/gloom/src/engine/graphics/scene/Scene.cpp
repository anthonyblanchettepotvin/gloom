#include "Scene.h"

#include "../../EngineGlobals.h"

void Scene::Register(const DirectionalLight& directionalLight)
{
	auto it = std::find(m_DirectionalLights.begin(), m_DirectionalLights.end(), &directionalLight);
	if (it == m_DirectionalLights.end())
	{
		m_DirectionalLights.push_back(&directionalLight);
	}
	else
	{
		gLogWarningMessage("Directional light is already registered to the scene.");
	}
}

void Scene::Register(const PointLight& pointLight)
{
	auto it = std::find(m_PointLights.begin(), m_PointLights.end(), &pointLight);
	if (it == m_PointLights.end())
	{
		m_PointLights.push_back(&pointLight);
	}
	else
	{
		gLogWarningMessage("Point light is already registered to the scene.");
	}
}

void Scene::Register(const Mesh& mesh)
{
	auto it = std::find(m_Meshes.begin(), m_Meshes.end(), &mesh);
	if (it == m_Meshes.end())
	{
		m_Meshes.push_back(&mesh);
	}
	else
	{
		gLogWarningMessage("Mesh is already registered to the scene.");
	}
}

void Scene::Register(const Skybox& skybox)
{
	auto it = std::find(m_Skyboxes.begin(), m_Skyboxes.end(), &skybox);
	if (it == m_Skyboxes.end())
	{
		m_Skyboxes.push_back(&skybox);
	}
	else
	{
		gLogWarningMessage("Skybox is already registered to the scene.");
	}
}

void Scene::Register(const Sprite& sprite)
{
	auto it = std::find(m_Sprites.begin(), m_Sprites.end(), &sprite);
	if (it == m_Sprites.end())
	{
		m_Sprites.push_back(&sprite);
	}
	else
	{
		gLogWarningMessage("Sprite is already registered to the scene.");
	}
}

void Scene::Unregister(const DirectionalLight& directionalLight)
{
	auto it = std::find(m_DirectionalLights.begin(), m_DirectionalLights.end(), &directionalLight);
	if (it != m_DirectionalLights.end())
	{
		m_DirectionalLights.erase(it);
	}
	else
	{
		gLogWarningMessage("Directional light is not registered to the scene.");
	}
}

void Scene::Unregister(const PointLight& pointLight)
{
	auto it = std::find(m_PointLights.begin(), m_PointLights.end(), &pointLight);
	if (it != m_PointLights.end())
	{
		m_PointLights.erase(it);
	}
	else
	{
		gLogWarningMessage("Point light is not registered to the scene.");
	}
}

void Scene::Unregister(const Mesh& mesh)
{
	auto it = std::find(m_Meshes.begin(), m_Meshes.end(), &mesh);
	if (it != m_Meshes.end())
	{
		m_Meshes.erase(it);
	}
	else
	{
		gLogWarningMessage("Mesh is not registered to the scene.");
	}
}

void Scene::Unregister(const Skybox& skybox)
{
	auto it = std::find(m_Skyboxes.begin(), m_Skyboxes.end(), &skybox);
	if (it != m_Skyboxes.end())
	{
		m_Skyboxes.erase(it);
	}
	else
	{
		gLogWarningMessage("Skybox is not registered to the scene.");
	}
}

void Scene::Unregister(const Sprite& sprite)
{
	auto it = std::find(m_Sprites.begin(), m_Sprites.end(), &sprite);
	if (it != m_Sprites.end())
	{
		m_Sprites.erase(it);
	}
	else
	{
		gLogWarningMessage("Sprite is not registered to the scene.");
	}
}
