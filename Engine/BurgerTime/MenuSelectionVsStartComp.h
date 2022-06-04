#pragma once
#include "MenuSelectionComp.h"

class MenuSelectionVsStartComp : public MenuSelectionComp
{
public:
	MenuSelectionVsStartComp();
	~MenuSelectionVsStartComp() = default;
	MenuSelectionVsStartComp(const MenuSelectionVsStartComp& other) = delete;
	MenuSelectionVsStartComp(MenuSelectionVsStartComp&& other) = delete;
	MenuSelectionVsStartComp& operator=(const MenuSelectionVsStartComp& other) = delete;
	MenuSelectionVsStartComp& operator=(MenuSelectionVsStartComp&& other) = delete;

	virtual void Activate();
};

