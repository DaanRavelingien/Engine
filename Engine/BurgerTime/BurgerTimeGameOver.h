#pragma once
#include <Scene.h>
#include <Command.h>

class BurgerTimeGameOver : public Scene
{
public:
	BurgerTimeGameOver() :Scene{ "BurgerTimeGameOver" } {};
	~BurgerTimeGameOver() = default;
	BurgerTimeGameOver(const BurgerTimeGameOver& other) = delete;
	BurgerTimeGameOver(BurgerTimeGameOver&& other) = delete;
	BurgerTimeGameOver& operator=(const BurgerTimeGameOver& other) = delete;
	BurgerTimeGameOver& operator=(BurgerTimeGameOver&& other) = delete;

protected:
	void Initialize() override;

private:
	//general inputs for this scene
	class ContiniuCmd : public Command
	{
	public:
		ContiniuCmd(GameObject* pGameObject) :Command{ pGameObject } {};
		void Execute() override;
	};
};

