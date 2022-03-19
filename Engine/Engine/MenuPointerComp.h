#pragma once
#include "Component.h"

class MenuPointerComp : public Component
{
public:
	MenuPointerComp();
	~MenuPointerComp() = default;
	MenuPointerComp(const MenuPointerComp& other) = delete;
	MenuPointerComp(MenuPointerComp&& other) = delete;
	MenuPointerComp& operator=(const MenuPointerComp& other) = delete;
	MenuPointerComp& operator=(MenuPointerComp&& other) = delete;

	void Initialize() override;

	int GetPointerPos() const { return m_PointerPos; };
	void MovePointerUp();
	void MovePointerDown();

private:
	int m_PointerPos{0};
	std::vector<glm::vec3> m_Positions{};
	glm::vec3 m_Offset{ -30,8,0 };
};

