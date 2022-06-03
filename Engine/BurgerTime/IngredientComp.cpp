#include "EnginePCH.h"
#include "IngredientComp.h"
#include "GameObject.h"
#include "Scene.h"

//component includes
#include "IngredientPieceComp.h"
#include "TransformComp.h"
#include "GravityComp.h"
#include "HitboxComp.h"

IngredientComp::IngredientComp()
	:Component{typeid(this).name()}
{
}

void IngredientComp::Initialize()
{
	//finding ingredient pieces
	for (GameObject* pChild : m_pGameObj->GetChildren())
	{
		if (pChild->GetComponent<IngredientPieceComp>())
			m_Pieces.push_back(pChild->GetComponent<IngredientPieceComp>());
	}

	//disable the gravity component
	m_pGameObj->GetComponent<GravityComp>()->Disable();
}

void IngredientComp::Update()
{
	switch (m_State)
	{
	case IngredientComp::State::Falling:
		UpdateFalling();
		break;
	case IngredientComp::State::OnPlatform:
		UpdateOnPlatform();
		break;
	case IngredientComp::State::OnTray:
	default:
		break;
	}
}

void IngredientComp::IsSteppedOn()
{
	float downOffset{ 3 };

	for (IngredientPieceComp* pPiece : m_Pieces)
	{
		//if a piece is trampled lower it
		if (pPiece->IsTrampled())
		{
			glm::vec3 newPos{ pPiece->GetGameObj()->GetTransform()->GetPos() - m_pGameObj->GetTransform()->GetPos()};

			newPos.y += downOffset;

			pPiece->GetGameObj()->GetTransform()->SetPos(newPos);
		}
	}

}

void IngredientComp::UpdateOnPlatform()
{
	//checking if all the ingredient pieces were trampled
	bool needsToFall{ true };
	for (IngredientPieceComp* pPiece : m_Pieces)
	{
		if (!pPiece->IsTrampled())
		{
			needsToFall = false;
			break;
		}
	}

	//checking if another ingredient fell on top
	if (!needsToFall)
	{
		for (HitboxComp* pHitbox : m_pGameObj->GetComponent<HitboxComp>()->GetOverlappingHitboxes())
		{
			if (pHitbox->GetTag() == HitboxTag::Ingredient)
			{
				//check if its actually above this ingredient
				if (pHitbox->GetGameObj()->GetTransform()->GetPos().y < m_pGameObj->GetTransform()->GetPos().y)
				{
					needsToFall = true;
					break;
				}
			}
		}
	}

	if (needsToFall)
	{
		//sending notification to the scene
		m_pGameObj->GetScene()->SendNotification(this, Event::BURGER_DROPS);

		m_State = State::Falling;

		//setting the old platform
		for (HitboxComp* pHitbox : m_pGameObj->GetComponent<HitboxComp>()->GetOverlappingHitboxes())
		{
			if (pHitbox->GetTag() == HitboxTag::Platform)
			{
				m_pOldPlatform = pHitbox;
				break;
			}
		}

		//enabeling the gravity component
		m_pGameObj->GetComponent<GravityComp>()->Enable();
	}
}

void IngredientComp::UpdateFalling()
{
	//if we found a new platform to land on reset the pieces and disable our falling
	if (FoundNewPlatform())
	{
		ResetPieces();
		//disabeling the gravity component
		m_pGameObj->GetComponent<GravityComp>()->Disable();

		//setting our y pos to the one of the platform

		m_State = State::OnPlatform;
		return;
	}

	//check if we found a tray or an ingredient that is on a tray
	for (HitboxComp* pHitbox : m_pGameObj->GetComponent<HitboxComp>()->GetOverlappingHitboxes())
	{
		//handeling encountering a tray
		if (pHitbox->GetTag() == HitboxTag::Tray)
		{
			//placing the ingredient in the tray
			float trayOffset{ 3 };

			glm::vec3 newPos{ m_pGameObj->GetTransform()->GetPos() - m_pGameObj->GetParent()->GetTransform()->GetPos() };
			newPos.y += trayOffset * m_pGameObj->GetTransform()->GetScale().y;
			m_pGameObj->GetTransform()->SetPos(newPos);

			ResetPieces();
			//disabeling the gravity component
			m_pGameObj->GetComponent<GravityComp>()->Disable();

			//setting our y pos to the one of the platform
			m_State = State::OnTray;
			return;
		}

		//handeling encountering an engredient that is already on a tray
		if (pHitbox->GetTag() == HitboxTag::Ingredient && pHitbox->GetGameObj()->GetComponent<IngredientComp>()->GetState() == State::OnTray)
		{
			float ingredientOffset{ 1 };

			//setting our y pos to the one of the platform
			glm::vec3 newPos{ pHitbox->GetGameObj()->GetTransform()->GetPos() - m_pGameObj->GetParent()->GetTransform()->GetPos()};
			newPos.x = m_pGameObj->GetTransform()->GetPos().x - m_pGameObj->GetParent()->GetTransform()->GetPos().x;
			newPos.y -= m_pGameObj->GetComponent<HitboxComp>()->GetSize().y;
			newPos.y -= ingredientOffset * m_pGameObj->GetTransform()->GetScale().y;
			m_pGameObj->GetTransform()->SetPos(newPos);

			ResetPieces();
			//disabeling the gravity component
			m_pGameObj->GetComponent<GravityComp>()->Disable();

			m_State = State::OnTray;
			return;
		}
	}
}

bool IngredientComp::FoundNewPlatform() const
{
	//checking for a new platform that is close enough
	for (HitboxComp* pHitbox : m_pGameObj->GetComponent<HitboxComp>()->GetOverlappingHitboxes())
	{
		if (pHitbox->GetTag() == HitboxTag::Platform && pHitbox != m_pOldPlatform)
		{
			//checking if the new platform is close enough
			float range{ -2 };
			float yPosIngredient{ m_pGameObj->GetTransform()->GetPos().y + m_pGameObj->GetComponent<HitboxComp>()->GetSize().y };
			float yPosPlatform{ pHitbox->GetGameObj()->GetTransform()->GetPos().y + pHitbox->GetSize().y };

			float distance{ yPosPlatform - yPosIngredient };

			if (range*m_pGameObj->GetTransform()->GetScale().y > distance)
				return true;
		}
	}

	return false;
}

void IngredientComp::ResetPieces()
{
	for (IngredientPieceComp* pPiece : m_Pieces)
	{
		pPiece->ResetPiece();
	}
}
