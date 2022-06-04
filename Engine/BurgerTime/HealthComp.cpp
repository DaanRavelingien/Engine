#include "EnginePCH.h"
#include "HealthComp.h"
#include "GameObject.h"
#include "HitboxComp.h"
#include <TransformComp.h>

HealthComp::HealthComp(int maxHealth)
	: Component{ typeid(this).name() }
	, m_Health{ maxHealth }
	,m_MaxHealth{maxHealth}
{
}

void HealthComp::Update()
{
	//checking if we are hit, or overlapping with an enemy
	HitboxComp* pPlayerHitbox{ m_pGameObj->GetComponent<HitboxComp>() };
	for (HitboxComp* pHitbox : pPlayerHitbox->GetOverlappingHitboxes())
	{
		if (pHitbox->GetTag() == HitboxTag::Enemy)
		{
			//checking if the enemy is close enough
			float enemyReach{ 5.f };
			
			glm::vec3 playerPos{ m_pGameObj->GetTransform()->GetPos() };
			glm::vec3 enemyPos{ pHitbox->GetGameObj()->GetTransform()->GetPos() };

			float distSq{};
			distSq = ((playerPos.x - enemyPos.x) * (playerPos.x - enemyPos.x)) + ((playerPos.y - enemyPos.y) * (playerPos.y - enemyPos.y));
			
			if (distSq < enemyReach * enemyReach)
			{
				Damage(1);
			}
		}
	}
}

void HealthComp::Damage(int damage)
{
	m_Health -= damage;
	
	if (m_Health < 0)
		m_Health = 0;

	m_pGameObj->SendNotification(this, Event::HEALTH_CHANGED);
}

void HealthComp::Heal(int heal)
{
	m_Health += heal;

	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;

	m_pGameObj->SendNotification(this, Event::HEALTH_CHANGED);
}
