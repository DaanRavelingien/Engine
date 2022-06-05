#pragma once
#include <Scene.h>
#include <Command.h>
#include <Observer.h>

class BurgerTimeVsLvl : public Scene, public Observer<Component>
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
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:

	//game objects
	GameObject* m_pPeterPepper{ nullptr };
	GameObject* m_pMrHotDog{ nullptr };

	GameObject* m_pLevel{ nullptr };

	GameObject* m_pScoreCounter{ nullptr };

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

