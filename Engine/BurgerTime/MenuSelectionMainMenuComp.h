#pragma once
#include "MenuSelectionComp.h"

class MenuSelectionMainMenuComp : public MenuSelectionComp
{
public:
	MenuSelectionMainMenuComp();
	~MenuSelectionMainMenuComp() = default;
	MenuSelectionMainMenuComp(const MenuSelectionMainMenuComp& other) = delete;
	MenuSelectionMainMenuComp(MenuSelectionMainMenuComp&& other) = delete;
	MenuSelectionMainMenuComp& operator=(const MenuSelectionMainMenuComp& other) = delete;
	MenuSelectionMainMenuComp& operator=(MenuSelectionMainMenuComp&& other) = delete;

	virtual void Activate();
};

