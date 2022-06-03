#include "EnginePCH.h"
#include "IngredientPieceComp.h"
#include "GameObject.h"

//component includes
#include "HitboxComp.h"
#include "TransformComp.h"
#include "IngredientComp.h"

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
				//checking if the player is close enough to be considdered on top
				float middleIngredientPart{ m_pGameObj->GetTransform()->GetPos().x + m_pHitbox->GetSize().x/2.f };
				float middlePlayer{ pHitbox->GetGameObj()->GetTransform()->GetPos().x + pHitbox->GetSize().x/2.f };
				float playerDist{ abs(middlePlayer - middleIngredientPart) };
				float ingrPartReach{ 10.f };

				if (ingrPartReach > playerDist)
				{
					m_IsTrampled = true;
					m_pGameObj->GetParent()->GetComponent<IngredientComp>()->IsSteppedOn();
				}
			}
		}
	}
}

void IngredientPieceComp::ResetPiece()
{
	//resetting the position
	glm::vec3 newPos{ m_pGameObj->GetTransform()->GetPos() - m_pGameObj->GetParent()->GetTransform()->GetPos() };
	newPos.y = 0;
	m_pGameObj->GetTransform()->SetPos(newPos);

	m_IsTrampled = false;
}
