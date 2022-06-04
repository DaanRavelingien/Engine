#pragma once
#include <Scene.h>
#include <Command.h>

class BurgerTimeVsLvl : public Scene
{
public:
	BurgerTimeVsLvl() :Scene{ "BurgerTimeVsLvl" } {};
	~BurgerTimeVsLvl() = default;
	BurgerTimeVsLvl(const BurgerTimeVsLvl& other) = delete;
	BurgerTimeVsLvl(BurgerTimeVsLvl&& other) = delete;
	BurgerTimeVsLvl& operator=(const BurgerTimeVsLvl& other) = delete;
	BurgerTimeVsLvl& operator=(BurgerTimeVsLvl&& other) = delete;

protected:
	void Initialize() override;

private:
	GameObject* m_pPeterPepper{ nullptr };
	GameObject* m_pMrHotDog{ nullptr };

	GameObject* m_pHud{ nullptr };

	//general inputs for this scene
	class PauseCmd : public Command
	{
	public:
		PauseCmd(GameObject* pGameObject) :Command{ pGameObject } {};
		void Execute() override;
	};
};

