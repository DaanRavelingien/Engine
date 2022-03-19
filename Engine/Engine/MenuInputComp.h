#pragma once
#include "Component.h"
#include "Command.h"

class MenuInputComp : public Component
{
public:
	MenuInputComp();
	~MenuInputComp() = default;
	MenuInputComp(const MenuInputComp& other) = delete;
	MenuInputComp(MenuInputComp&& other) = delete;
	MenuInputComp& operator=(const MenuInputComp& other) = delete;
	MenuInputComp& operator=(MenuInputComp&& other) = delete;

	void Initialize() override;

};

class MenuUpCmd : public Command
{
public:
	MenuUpCmd(GameObject* pGameObj, Component* pComp) :Command{ pGameObj }, m_pComp{ pComp } {};
	void Execute() override;

private:
	Component* m_pComp{ nullptr };
};

class MenuDownCmd : public Command
{
public:
	MenuDownCmd(GameObject* pGameObj, Component* pComp) :Command{ pGameObj }, m_pComp{ pComp } {};
	void Execute() override;

private:
	Component* m_pComp{ nullptr };
};

class MenuSelectCmd : public Command
{
public:
	MenuSelectCmd(GameObject* pGameObj, Component* pComp) :Command{ pGameObj }, m_pComp{ pComp } {};
	void Execute() override;

private:
	Component* m_pComp{ nullptr };
};
