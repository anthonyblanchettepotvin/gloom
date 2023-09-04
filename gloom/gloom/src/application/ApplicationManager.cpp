#include "ApplicationManager.h"

void ApplicationManager::SelectObject(Object* object)
{
	m_SelectedObject = object;
}

bool ApplicationManager::IsObjectSelected(Object* object)
{
	return m_SelectedObject != nullptr && object != nullptr && m_SelectedObject == object;
}
