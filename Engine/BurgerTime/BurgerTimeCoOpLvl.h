#pragma once
#include <Scene.h>
#include <Command.h>
#include <Observer.h>

class BurgerTimeCoOpLvl : public Scene, public Observer<Component>
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
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:
	GameObject* m_pPeterPepper{ nullptr };
	GameObject* m_pSallySalt{ nullptr };

	GameObject* m_pLevel{ nullptr };

	GameObject* m_pScoreCounter{ nullptr };
	GameObject* m_pGameOverHud{ nullptr };

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

