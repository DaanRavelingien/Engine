#pragma once
#include "Scene.h"

class BurgerTimeOptionsMenu : public Scene
{
public:
	BurgerTimeOptionsMenu() :Scene{ "BurgerTimeOptionsMenu" } {};
	~BurgerTimeOptionsMenu() = default;
	BurgerTimeOptionsMenu(const BurgerTimeOptionsMenu& other) = delete;
	BurgerTimeOptionsMenu(BurgerTimeOptionsMenu&& other) = delete;
	BurgerTimeOptionsMenu& operator=(const BurgerTimeOptionsMenu& other) = delete;
	BurgerTimeOptionsMenu& operator=(BurgerTimeOptionsMenu&& other) = delete;

protected:
	void Initialize() override;
};

