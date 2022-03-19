#pragma once
#include "Scene.h"

class BurgerTimePauseMenu : public Scene
{
public:
	BurgerTimePauseMenu() :Scene{ "BurgerTimePauseMenu" } {};
	~BurgerTimePauseMenu() = default;
	BurgerTimePauseMenu(const BurgerTimePauseMenu& other) = delete;
	BurgerTimePauseMenu(BurgerTimePauseMenu&& other) = delete;
	BurgerTimePauseMenu& operator=(const BurgerTimePauseMenu& other) = delete;
	BurgerTimePauseMenu& operator=(BurgerTimePauseMenu&& other) = delete;

protected:
	void Initialize() override;
};

