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

	virtual void Activate() = 0;
};

