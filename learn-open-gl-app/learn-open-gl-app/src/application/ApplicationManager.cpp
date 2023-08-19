#include "ApplicationManager.h"

void ApplicationManager::SelectObject(const Object& object)
{
	if (m_SelectedObject == &object)
		return;
	
	m_SelectedObject = &object;
}
