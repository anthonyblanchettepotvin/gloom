#pragma once

class Object;

class ApplicationManager
{
public:
	void SelectObject(Object& object);

	Object* GetSelectedObject() { return m_SelectedObject; }

private:
	Object* m_SelectedObject = nullptr;
};
