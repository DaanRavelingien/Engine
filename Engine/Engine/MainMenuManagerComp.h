#pragma once
#include "Component.h"

class MenuPointerComp;

class MainMenuManagerComp : public Component
{
public:
	MainMenuManagerComp();
	~MainMenuManagerComp() = default;
	MainMenuManagerComp(const MainMenuManagerComp& other) = delete;
	MainMenuManagerComp(MainMenuManagerComp&& other) = delete;
	MainMenuManagerComp& operator=(const MainMenuManagerComp& other) = delete;
	MainMenuManagerComp& operator=(MainMenuManagerComp&& other) = delete;

	void Initialize() override;

	void SelectNext();
	void SelectPrev();
	void Select();


private:
	MenuPointerComp* m_pMenuPointerComp{nullptr};
	std::string m_SelectedMenuOption{};
	std::vector<std::string> m_MenuOptions{};
};

