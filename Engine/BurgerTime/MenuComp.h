#pragma once
#include "Component.h"

class MenuComp : public Component
{
public:
	MenuComp();
	~MenuComp() = default;
	MenuComp(const MenuComp& other) = delete;
	MenuComp(MenuComp&& other) = delete;
	MenuComp& operator=(const MenuComp& other) = delete;
	MenuComp& operator=(MenuComp&& other) = delete;

	void Initialize() override;

	void SelectNext();
	void SelectPrev();
	void Select();

private:
	int m_SelectedOption{};

	glm::vec3 m_MenuPointerOffset{ -30,8,0 };

	void UpdateMenuPointer();
};