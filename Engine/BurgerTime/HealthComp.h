#pragma once
#include "Component.h"

class HealthComp final : public Component
{
public:
	HealthComp(int maxHealth);
	~HealthComp() = default;
	HealthComp(const HealthComp& other) = delete;
	HealthComp(HealthComp&& other) = delete;
	HealthComp& operator=(const HealthComp& other) = delete;
	HealthComp& operator=(HealthComp&& other) = delete;

	void Update() override;

	int GetHealth() const {	return m_Health; };
	int GetMaxHealth() const { return m_MaxHealth; };

	void Reset();

	void Damage(int damage);
	void Heal(int heal);

private:
	int m_Health{};
	int m_MaxHealth{};
};

