#pragma once
#include <Component.h>
#include <Observer.h>

class EnemyComp : public Component, public Observer<Component>
{
public:
	enum class EnemyType
	{
		MrHotDog, MrPickle, MrEgg
	};

	EnemyComp(EnemyType type);
	~EnemyComp() = default;
	EnemyComp(const EnemyComp& other) = delete;
	EnemyComp(EnemyComp&& other) = delete;
	EnemyComp& operator=(const EnemyComp& other) = delete;
	EnemyComp& operator=(EnemyComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	EnemyType GetEnemyType() const { return m_EnemyType; };
	bool IsDead() const { return m_IsDead; };

	void Disable();
	void Kill();

private:
	EnemyType m_EnemyType;
	bool m_IsDead{ false };

	float m_RespawnHeight{750};

	void Notify(Component* pComp, Event event) override;
};

