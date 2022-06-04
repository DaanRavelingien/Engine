#pragma once
#include "Component.h"

class IngredientPieceComp;
class HitboxComp;

class IngredientComp : public Component
{
public:
	enum class State
	{
		Falling, OnPlatform, OnTray
	};

	IngredientComp();
	~IngredientComp() = default;
	IngredientComp(const IngredientComp& other) = delete;
	IngredientComp(IngredientComp&& other) = delete;
	IngredientComp& operator=(const IngredientComp& other) = delete;
	IngredientComp& operator=(IngredientComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	void IsSteppedOn();
	State GetState() const { return m_State; };

private:
	std::vector<IngredientPieceComp*> m_Pieces{};
	State m_State{ State::OnPlatform };
	HitboxComp* m_pOldPlatform{ nullptr };
	std::vector<GameObject*> m_EnemiesOnTop{};

	void UpdateOnPlatform();
	void UpdateFalling();

	HitboxComp* FindNewPlatform();
	void ResetPieces();

	void HandleEnemiesOnTopFalling();
};

