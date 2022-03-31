#pragma once
#include "Scene.h"
#include "Command.h"

class BurgerTimeLvl final: public Scene
{
public:
	BurgerTimeLvl() :Scene{ "BurgerTimeLvl" } {};
	~BurgerTimeLvl() = default;
	BurgerTimeLvl(const BurgerTimeLvl& other) = delete;
	BurgerTimeLvl(BurgerTimeLvl&& other) = delete;
	BurgerTimeLvl& operator=(const BurgerTimeLvl& other) = delete;
	BurgerTimeLvl& operator=(BurgerTimeLvl&& other) = delete;

	GameObject* GetHitboxManager() const { return m_pHitboxManager; };

protected:
	void Initialize() override;

private:
	GameObject* m_pHitboxManager{ nullptr };
	GameObject* m_pPeterPepper{ nullptr };
	GameObject* m_pHud{ nullptr };

	//general inputs for this scene
	class PauseCmd : public Command
	{
	public:
		PauseCmd(GameObject* pGameObject) :Command{ pGameObject } {};
		void Execute() override;
	};
};

