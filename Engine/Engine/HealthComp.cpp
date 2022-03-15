#include "EnginePCH.h"
#include "HealthComp.h"

HealthComp::HealthComp(int maxHealth)
	: Component(typeid(this).name())
	,m_MaxHealth{maxHealth}
{
}

void HealthComp::Damage(int damage)
{
	m_Health -= damage;
	
	if (m_Health < 0)
		m_Health = 0;
}

void HealthComp::Heal(int heal)
{
	m_Health += heal;

	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;
}
