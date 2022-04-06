#include "EnginePCH.h"
#include "IngredientPieceComp.h"
#include "GameObject.h"

//component includes
#include "HitboxComp.h"
#include "TransformComp.h"

IngredientPieceComp::IngredientPieceComp()
	:Component{typeid(this).name()}
{
}

void IngredientPieceComp::Initialize()
{
	//finding the hitbox of the ingredient piece
	m_pHitbox = m_pGameObj->GetComponent<HitboxComp>();
}

void IngredientPieceComp::Update()
{
	if (!m_IsTrampled && m_pHitbox)
	{
		//check if the player is on it and if so lower the ingrdient to indicate it
		for (HitboxComp* pHitbox : m_pHitbox->GetOverlappingHitboxes())
		{
			if (pHitbox->GetTag() == HitboxTag::Player)
			{
				m_IsTrampled = true;
				LowerIngredientPart();
			}
		}
	}
}

void IngredientPieceComp::LowerIngredientPart()
{
	float downOffset{ 10 };
	glm::vec3 newPos{ m_pGameObj->GetTransform()->GetPos() - m_pGameObj->GetParent()->GetTransform()->GetPos() };

	newPos.y += downOffset;

	m_pGameObj->GetTransform()->SetPos(newPos);
}
