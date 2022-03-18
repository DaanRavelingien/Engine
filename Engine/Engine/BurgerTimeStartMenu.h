#pragma once
#include "Scene.h"



class BurgerTimeStartMenu final : public Scene
{
public:
	BurgerTimeStartMenu() :Scene{ "BurgerTimeMainMenu" } {};
	~BurgerTimeStartMenu() = default;
	BurgerTimeStartMenu(const BurgerTimeStartMenu& other) = delete;
	BurgerTimeStartMenu(BurgerTimeStartMenu&& other) = delete;
	BurgerTimeStartMenu& operator=(const BurgerTimeStartMenu& other) = delete;
	BurgerTimeStartMenu& operator=(BurgerTimeStartMenu&& other) = delete;

protected:

	void Initialize() override;
	void Update() override;

private:

};

