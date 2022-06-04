#pragma once
#include <Scene.h>
#include <Command.h>

class BurgerTimeCoOpLvl : public Scene
{
public:
	BurgerTimeCoOpLvl() :Scene{ "BurgerTimeCoOpLvl" } {};
	~BurgerTimeCoOpLvl() = default;
	BurgerTimeCoOpLvl(const BurgerTimeCoOpLvl& other) = delete;
	BurgerTimeCoOpLvl(BurgerTimeCoOpLvl&& other) = delete;
	BurgerTimeCoOpLvl& operator=(const BurgerTimeCoOpLvl& other) = delete;
	BurgerTimeCoOpLvl& operator=(BurgerTimeCoOpLvl&& other) = delete;

protected:
	void Initialize() override;

private:
	GameObject* m_pPeterPepper{ nullptr };
	GameObject* m_pSallySalt{ nullptr };

	GameObject* m_pHud{ nullptr };

	//general inputs for this scene
	class PauseCmd : public Command
	{
	public:
		PauseCmd(GameObject* pGameObject) :Command{ pGameObject } {};
		void Execute() override;
	};
};

