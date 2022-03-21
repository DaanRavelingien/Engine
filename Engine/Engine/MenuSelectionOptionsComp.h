#pragma once
#include "MenuSelectionComp.h"
class MenuSelectionOptionsComp : public MenuSelectionComp
{
public:
	MenuSelectionOptionsComp();
	~MenuSelectionOptionsComp() = default;
	MenuSelectionOptionsComp(const MenuSelectionOptionsComp& other) = delete;
	MenuSelectionOptionsComp(MenuSelectionOptionsComp&& other) = delete;
	MenuSelectionOptionsComp& operator=(const MenuSelectionOptionsComp& other) = delete;
	MenuSelectionOptionsComp& operator=(MenuSelectionOptionsComp&& other) = delete;

	virtual void Activate();
};

