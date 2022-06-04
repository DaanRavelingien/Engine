#include "EnginePCH.h"
#include "EnemyComp.h"
#include <GameObject.h>
#include "EntityMoveComp.h"
#include "GravityComp.h"
#include "TransformComp.h"
#include <Scene.h>

EnemyComp::EnemyComp(EnemyType type)
	:Component{typeid(this).name()}
	,m_EnemyType{type}
{
}

void EnemyComp::Initialize()
{
	//adding this component as an observer to its game object
	m_pGameObj->AddObserver(this);

	//disabeling the gravity component
	GravityComp* pGravity{ m_pGameObj->GetComponent<GravityComp>() };

	if (pGravity)
		pGravity->Disable();
}

void EnemyComp::Update()
{
	if (m_IsDead)
	{
		float height{ m_pGameObj->GetTransform()->GetPos().y };

		if (height > m_RespawnHeight)
		{
			m_IsDead = false;

			//respawning and resetting the enemy
			GravityComp* pGravity{ m_pGameObj->GetComponent<GravityComp>() };
			if (pGravity)
				pGravity->Disable();

			EntityMoveComp* pEntityMoveComp{ m_pGameObj->GetComponent<EntityMoveComp>() };

			if (pEntityMoveComp)
			{
				pEntityMoveComp->Enable();
				pEntityMoveComp->Respawn();
			}
		}
	}
}

void EnemyComp::Disable()
{
	//find the entity movement component and disable it
	m_pGameObj->GetComponent<EntityMoveComp>()->Disable();
}

void EnemyComp::Kill()
{
	if (m_IsDead)
		return;

	//disable the movement for the enemy
	Disable();

	//find a gravity component and enable it
	GravityComp* pGravity{ m_pGameObj->GetComponent<GravityComp>() };

	if (pGravity)
		pGravity->Enable();

	m_IsDead = true;

	//sending message to the level to update the score
	switch (m_EnemyType)
	{
	case EnemyComp::EnemyType::MrHotDog:
		m_pGameObj->GetScene()->SendNotification(this, Event::HOTDOG_DIES);
		break;
	case EnemyComp::EnemyType::MrPickle:
		m_pGameObj->GetScene()->SendNotification(this, Event::PICLE_DIES);
		break;
	case EnemyComp::EnemyType::MrEgg:
		m_pGameObj->GetScene()->SendNotification(this, Event::EGG_DIES);
		break;
	default:
		break;
	}
}

void EnemyComp::Notify(Component*, Event event)
{
	if (event == Event::ENEMY_DROPPED || event == Event::ENEMY_CRUSHED)
		Kill();
}
