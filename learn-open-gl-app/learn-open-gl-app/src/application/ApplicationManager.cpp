#include "ApplicationManager.h"

void ApplicationManager::SelectObject(const Object& object)
{
	if (m_SelectedObject == &object)
		return;
	
	m_SelectedObject = const_cast<Object*>(&object); // TODO: Get rid of const_cast somehow
}
