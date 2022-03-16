#pragma once
#include "Scene.h"
class BurgerTimeLvl final: public Scene
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
	void Update() override;

private:
	GameObject* m_pPeterPepper{ nullptr };
	GameObject* m_pHud{ nullptr };
};

