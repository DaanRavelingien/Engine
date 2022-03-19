#pragma once
#include "MenuSelectionComp.h"

class MenuSelectionExitComp : public MenuSelectionComp
{
public:
	MenuSelectionExitComp();
	~MenuSelectionExitComp() = default;
	MenuSelectionExitComp(const MenuSelectionExitComp& other) = delete;
	MenuSelectionExitComp(MenuSelectionExitComp&& other) = delete;
	MenuSelectionExitComp& operator=(const MenuSelectionExitComp& other) = delete;
	MenuSelectionExitComp& operator=(MenuSelectionExitComp&& other) = delete;

	virtual void Activate();
};

