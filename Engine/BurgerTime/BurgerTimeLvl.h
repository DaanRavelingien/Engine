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

private:	
	GameObject* m_pPeterPepper{ nullptr };

	GameObject* m_pEnemyManager{ nullptr };

	GameObject* m_pLevel{ nullptr };
	GameObject* m_pScoreCounter{ nullptr };;

	//general inputs for this scene
	class PauseCmd : public Command
	{
	public:
		PauseCmd(GameObject* pGameObject) :Command{ pGameObject } {};
		void Execute() override;
	};

	void Notify(Component* pComp, Event event) override;
	void ResetScene();
};

