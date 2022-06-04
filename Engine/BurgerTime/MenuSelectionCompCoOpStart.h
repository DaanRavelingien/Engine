#pragma once
#include "MenuSelectionComp.h"

class MenuSelectionCompCoOpStart : public MenuSelectionComp
{
public:
	MenuSelectionCompCoOpStart();
	~MenuSelectionCompCoOpStart() = default;
	MenuSelectionCompCoOpStart(const MenuSelectionCompCoOpStart& other) = delete;
	MenuSelectionCompCoOpStart(MenuSelectionCompCoOpStart&& other) = delete;
	MenuSelectionCompCoOpStart& operator=(const MenuSelectionCompCoOpStart& other) = delete;
	MenuSelectionCompCoOpStart& operator=(MenuSelectionCompCoOpStart&& other) = delete;

	virtual void Activate();
};

