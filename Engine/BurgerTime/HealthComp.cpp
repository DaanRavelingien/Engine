#include "EnginePCH.h"
#include "HealthComp.h"
#include "GameObject.h"

HealthComp::HealthComp(int maxHealth)
	: Component{ typeid(this).name() }
	, m_Health{ maxHealth }
	,m_MaxHealth{maxHealth}
{
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
