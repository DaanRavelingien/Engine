#pragma once
#include "MenuSelectionComp.h"
class MenuSelectionStartComp : public MenuSelectionComp
{
public:
	MenuSelectionStartComp();
	~MenuSelectionStartComp() = default;
	MenuSelectionStartComp(const MenuSelectionStartComp& other) = delete;
	MenuSelectionStartComp(MenuSelectionStartComp&& other) = delete;
	MenuSelectionStartComp& operator=(const MenuSelectionStartComp& other) = delete;
	MenuSelectionStartComp& operator=(MenuSelectionStartComp&& other) = delete;

	virtual void Activate();
};

