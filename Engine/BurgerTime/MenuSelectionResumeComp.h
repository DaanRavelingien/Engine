#pragma once
#include "MenuSelectionComp.h"

class MenuSelectionResumeComp : public MenuSelectionComp
{
public:
	MenuSelectionResumeComp();
	~MenuSelectionResumeComp() = default;
	MenuSelectionResumeComp(const MenuSelectionResumeComp& other) = delete;
	MenuSelectionResumeComp(MenuSelectionResumeComp&& other) = delete;
	MenuSelectionResumeComp& operator=(const MenuSelectionResumeComp& other) = delete;
	MenuSelectionResumeComp& operator=(MenuSelectionResumeComp&& other) = delete;

	virtual void Activate();
};

