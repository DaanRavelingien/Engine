#pragma once
#include "Scene.h"
#include "Command.h"
#include <Observer.h>

class BurgerTimeLvl final: public Scene, public Observer<Component>
{
public:
	BurgerTimeLvl() :Scene{ "BurgerTimeLvl" } {};
	~BurgerTimeLvl() = default;
	BurgerTimeLvl(const BurgerTimeLvl& other) = delete;
	BurgerTimeLvl(BurgerTimeLvl&& other) = delete;
	BurgerTimeLvl& operator=(const BurgerTimeLvl& other) = delete;
	BurgerTimeLvl& operator=(BurgerTimeLvl&& other) = delete;

protected:
	void Initialize() override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:	
	GameObject* m_pPeterPepper{ nullptr };

	GameObject* m_pLevel{ nullptr };
	GameObject* m_pScoreCounter{ nullptr };

	GameObject* m_pGameOverHud{ nullptr };
;

	//general inputs for this scene
	class PauseCmd : public Command
	{
	public:
		PauseCmd(GameObject* pGameObject) :Command{ pGameObject } {};
		void Execute() override;
	};
	class GameOverCmd : public Command
	{
	public:
		GameOverCmd(GameObject* pGameObject) :Command{ pGameObject } {};
		void Execute() override;
	};

	void Notify(Component* pComp, Event event) override;
};

