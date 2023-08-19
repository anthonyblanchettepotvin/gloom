#pragma once

#include <memory>

class Object;

class ApplicationManager
{
public:
	void SelectObject(const Object& object);

	const Object* GetSelectedObject() const { return m_SelectedObject; }

private:
	const Object* m_SelectedObject = nullptr;
};
