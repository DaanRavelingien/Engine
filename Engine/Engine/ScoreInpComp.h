#pragma once
#include "Component.h"
#include "Command.h"

enum class Controller;

class ScoreInpComp : public Component
{
public:
	ScoreInpComp(Controller inpController);
	~ScoreInpComp() = default;
	ScoreInpComp(const ScoreInpComp& other) = delete;
	ScoreInpComp(ScoreInpComp&& other) = delete;
	ScoreInpComp& operator=(const ScoreInpComp& other) = delete;
	ScoreInpComp& operator=(ScoreInpComp&& other) = delete;

	void Initialize() override;
private:
	Controller m_InpController{};
};

class EnemyDiedCmd : public Command
{
public:
	EnemyDiedCmd(GameObject* pGameObj, Component* pComp) :Command{ pGameObj }, m_pComp{ pComp } {};
	void Execute() override;

private:
	Component* m_pComp{ nullptr };
};

class BurgerDorpCmd : public Command
{
public:
	BurgerDorpCmd(GameObject* pGameObj, Component* pComp) :Command{ pGameObj }, m_pComp{pComp} {};
	void Execute() override;

private:
	Component* m_pComp{ nullptr };
};

