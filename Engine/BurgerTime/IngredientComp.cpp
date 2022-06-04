#include "EnginePCH.h"
#include "IngredientComp.h"
#include "GameObject.h"
#include "Scene.h"

//component includes
#include "IngredientPieceComp.h"
#include "TransformComp.h"
#include "GravityComp.h"
#include "HitboxComp.h"
#include "EnemyComp.h"

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
				//check if its actually above this ingredient and if its falling
				if (pHitbox->GetGameObj()->GetTransform()->GetPos().y < m_pGameObj->GetTransform()->GetPos().y
					&& pHitbox->GetGameObj()->GetComponent<IngredientComp>()->GetState() == State::Falling)
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
			if (pHitbox->GetTag() == HitboxTag::Platform && !m_pOldPlatform)
			{
				m_pOldPlatform = pHitbox;
			}
			//also checking if any enemies were on top
			else if(pHitbox->GetTag() == HitboxTag::Enemy)
			{
				//checking if the enemies are still alive
				if (!pHitbox->GetGameObj()->GetComponent<EnemyComp>()->IsDead())
					m_EnemiesOnTop.push_back(pHitbox->GetGameObj());
			}
		}

		//handeling the enemies that were on top
		HandleEnemiesOnTopFalling();

		//enabeling the gravity component
		m_pGameObj->GetComponent<GravityComp>()->Enable();
	}
}

void IngredientComp::UpdateFalling()
{
	//check if we found a tray or an ingredient that is on a tray
	for (HitboxComp* pHitbox : m_pGameObj->GetComponent<HitboxComp>()->GetOverlappingHitboxes())
	{
		//handeling encountering a tray
		if (pHitbox->GetTag() == HitboxTag::Tray)
		{
			//placing the ingredient in the tray
			float trayOffset{ 3 };

			//setting our y pos to the one of the platform
			glm::vec3 newPos{ m_pGameObj->GetTransform()->GetPos() - m_pGameObj->GetParent()->GetTransform()->GetPos() };
			newPos.y += trayOffset * m_pGameObj->GetTransform()->GetScale().y;
			m_pGameObj->GetTransform()->SetPos(newPos);

			ResetPieces();
			//disabeling the gravity component
			m_pGameObj->GetComponent<GravityComp>()->Disable();

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

		//killing any enemy we fall on
		if (pHitbox->GetTag() == HitboxTag::Enemy)
		{
			//checking if the overlapping hitbox is not one of the enemies that was on top
			auto it = std::find(m_EnemiesOnTop.begin(), m_EnemiesOnTop.end(), pHitbox->GetGameObj());
			if (it == m_EnemiesOnTop.end())
				pHitbox->GetGameObj()->SendNotification(this, Event::ENEMY_CRUSHED);

		}
	}

	//if we found a new platform to land on reset the pieces and disable our falling
	HitboxComp* newPlatform{ FindNewPlatform() };
	if (newPlatform)
	{
		//setting our y pos to the one of the platform
		glm::vec3 newPos{ m_pGameObj->GetTransform()->GetPos() - m_pGameObj->GetParent()->GetTransform()->GetPos() };

		newPos.y = newPlatform->GetGameObj()->GetTransform()->GetPos().y + newPlatform->GetSize().y - m_pGameObj->GetComponent<HitboxComp>()->GetSize().y;
		newPos.y -= m_pGameObj->GetParent()->GetTransform()->GetPos().y;

		float platformThickness{ 2.f * newPlatform->GetGameObj()->GetTransform()->GetScale().y };

		newPos.y += platformThickness;

		m_pGameObj->GetTransform()->SetPos(newPos);

		ResetPieces();

		//disabeling the gravity component
		m_pGameObj->GetComponent<GravityComp>()->Disable();

		m_State = State::OnPlatform;
		return;
	}
}

HitboxComp* IngredientComp::FindNewPlatform()
{
	//checking for a new platform that is close enough
	for (HitboxComp* pHitbox : m_pGameObj->GetComponent<HitboxComp>()->GetOverlappingHitboxes())
	{
		if (pHitbox->GetTag() == HitboxTag::Platform && pHitbox != m_pOldPlatform)
		{
			float yPosIngr{ m_pGameObj->GetTransform()->GetPos().y + m_pGameObj->GetComponent<HitboxComp>()->GetSize().y };
			float yPosPlatfrm{ pHitbox->GetGameObj()->GetTransform()->GetPos().y + pHitbox->GetSize().y };
			float dist{ std::abs(yPosPlatfrm - yPosIngr) };
			float range{ 5.f };

			if (range > dist)
			{
				m_pOldPlatform = nullptr;
				return pHitbox;
			}
		}
	}

	return nullptr;
}

void IngredientComp::ResetPieces()
{
	for (IngredientPieceComp* pPiece : m_Pieces)
	{
		pPiece->ResetPiece();
	}
}

void IngredientComp::HandleEnemiesOnTopFalling()
{
	//send the needed events for our score system
	switch ((int)m_EnemiesOnTop.size())
	{
	case 1:
		m_pGameObj->GetScene()->SendNotification(this, Event::BURGER_DROPS_1_ENEMY);
		break;
	case 2:
		m_pGameObj->GetScene()->SendNotification(this, Event::BURGER_DROPS_2_ENEMYS);
		break;
	case 3:
		m_pGameObj->GetScene()->SendNotification(this, Event::BURGER_DROPS_3_ENEMYS);
		break;
	case 4:
		m_pGameObj->GetScene()->SendNotification(this, Event::BURGER_DROPS_4_ENEMYS);
		break;
	case 5:
		m_pGameObj->GetScene()->SendNotification(this, Event::BURGER_DROPS_5_ENEMYS);
		break;
	case 6:
		m_pGameObj->GetScene()->SendNotification(this, Event::BURGER_DROPS_6_ENEMYS);
		break;
	default:
		break;
	}

	//and sent the needed events to our enemies
	for (GameObject* pEnemy : m_EnemiesOnTop)
	{
		pEnemy->SendNotification(this, Event::ENEMY_DROPPED);
	}

	m_EnemiesOnTop.clear();
}
