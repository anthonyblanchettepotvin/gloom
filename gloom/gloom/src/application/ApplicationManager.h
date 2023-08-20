#pragma once

#include <memory>

class Object;

class ApplicationManager
{
public:
	void SelectObject(Object& object);

	Object* GetSelectedObject() const { return m_SelectedObject; }

private:
	Object* m_SelectedObject = nullptr;
};
