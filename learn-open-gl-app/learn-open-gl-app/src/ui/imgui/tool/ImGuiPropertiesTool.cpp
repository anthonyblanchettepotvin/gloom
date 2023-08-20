#include "ImGuiPropertiesTool.h"

#include <memory>

#include "../../../vendor/imgui/imgui.h"

#include "../../../application/ApplicationManager.h"
#include "../../../engine/object/Object.h"

#include "../ImGuiAdapter.h"
#include "../ImGuiAdapterFactory.h"

#define PROPERTIES_TOOL_NAME "Properties"

ImGuiPropertiesTool::ImGuiPropertiesTool(ImGuiAdapterFactory& adapterFactory, ApplicationManager& applicationManager, GraphicsEngine& graphicsEngine)
	: m_AdapterFactory(adapterFactory), m_ApplicationManager(applicationManager), m_GraphicsEngine(graphicsEngine)
{
}

void ImGuiPropertiesTool::Render()
{
	ImGui::Begin(PROPERTIES_TOOL_NAME);

	Object* selectedObject = m_ApplicationManager.GetSelectedObject();
	if (selectedObject)
	{
		std::unique_ptr<ImGuiAdapter> selectedObjectAdapter = m_AdapterFactory.CreateAdapter(selectedObject);
		if (selectedObjectAdapter)
		{
			selectedObjectAdapter->Render();
		}
	}

	ImGui::End();
}
