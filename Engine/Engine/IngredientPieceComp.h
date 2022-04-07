#pragma once
#include "Component.h"

class HitboxComp;

class IngredientPieceComp : public Component
{
public:
	IngredientPieceComp();
	~IngredientPieceComp() = default;
	IngredientPieceComp(const IngredientPieceComp& other) = delete;
	IngredientPieceComp(IngredientPieceComp&& other) = delete;
	IngredientPieceComp& operator=(const IngredientPieceComp& other) = delete;
	IngredientPieceComp& operator=(IngredientPieceComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	void ResetPiece();
	bool IsTrampled() const { return m_IsTrampled; };

private:
	bool m_IsTrampled{ false };

	HitboxComp* m_pHitbox{ nullptr };

};

