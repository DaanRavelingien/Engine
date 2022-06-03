#pragma once
#include "Component.h"

class MenuSelectionComp : public Component
{
public:
	MenuSelectionComp(const std::string& name);
	~MenuSelectionComp() = default;
	MenuSelectionComp(const MenuSelectionComp& other) = delete;
	MenuSelectionComp(MenuSelectionComp&& other) = delete;
	MenuSelectionComp& operator=(const MenuSelectionComp& other) = delete;
	MenuSelectionComp& operator=(MenuSelectionComp&& other) = delete;

	bool IsSelected() const { return m_IsSelected; };
	void Select() { m_IsSelected = true; };
	void Deselect() { m_IsSelected = false; };

	virtual void Activate() = 0;

private:
	bool m_IsSelected{ false };
};

