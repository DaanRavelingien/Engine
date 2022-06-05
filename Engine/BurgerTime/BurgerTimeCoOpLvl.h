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

private:
	GameObject* m_pPeterPepper{ nullptr };
	GameObject* m_pSallySalt{ nullptr };

	GameObject* m_pEnemyManager{ nullptr };

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

