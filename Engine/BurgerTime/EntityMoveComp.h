#pragma once
#include "Component.h"
#include "Observer.h"

class HitboxComp;

class EntityMoveComp : public Component, public Observer<Component>
{
public:
	EntityMoveComp(const glm::vec2& spawnPosition);
	~EntityMoveComp() = default;
	EntityMoveComp(const EntityMoveComp& other) = delete;
	EntityMoveComp(EntityMoveComp&& other) = delete;
	EntityMoveComp& operator=(const EntityMoveComp& other) = delete;
	EntityMoveComp& operator=(EntityMoveComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	void Respawn();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

private:
	void FindLadder();
	void FindPlatform();

	void Notify(Component* pComp, Event event) override;

	HitboxComp* m_pHitbox{ nullptr };
	float m_Reach{ 10.f };
	float m_MoveSpeed{ 100.f };

	glm::vec2 m_spawnPos{};

	//TODO: create platform comp and ladder comp
	GameObject* m_pPlatform{ nullptr };
	GameObject* m_pLadder{ nullptr };
};

