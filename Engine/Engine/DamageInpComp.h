#pragma once
#include "Component.h"
#include "Command.h"

class DamageInpComp : public Component
{
public:
	DamageInpComp();
	~DamageInpComp() = default;
	DamageInpComp(const DamageInpComp& other) = delete;
	DamageInpComp(DamageInpComp&& other) = delete;
	DamageInpComp& operator=(const DamageInpComp& other) = delete;
	DamageInpComp& operator=(DamageInpComp&& other) = delete;

	void Initialize() override;

private:
	void CreateCommands();

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
