#pragma once
#include "Component.h"
#include "Command.h"

enum class Controller;

class DamageInpComp : public Component
{
public:
	DamageInpComp(Controller inpController);
	~DamageInpComp() = default;
	DamageInpComp(const DamageInpComp& other) = delete;
	DamageInpComp(DamageInpComp&& other) = delete;
	DamageInpComp& operator=(const DamageInpComp& other) = delete;
	DamageInpComp& operator=(DamageInpComp&& other) = delete;

	void Initialize() override;

private:
	Controller m_InpController{};
	GameObject* m_pPeterPepper{ nullptr };
};

//commands
class Damage : public Command
{
public:
	Damage(GameObject* pGameObj) : Command{ pGameObj } {};
	void Execute() override;
};

class Heal : public Command
{
public:
	Heal(GameObject* pGameObj) : Command{ pGameObj } {};
	void Execute() override;
};
