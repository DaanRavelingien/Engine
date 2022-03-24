#pragma once
#include "Component.h"

class HitboxComp;

class EntityMoveComp : public Component
{
public:
	EntityMoveComp(GameObject* pStartPlatform);
	~EntityMoveComp() = default;
	EntityMoveComp(const EntityMoveComp& other) = delete;
	EntityMoveComp(EntityMoveComp&& other) = delete;
	EntityMoveComp& operator=(const EntityMoveComp& other) = delete;
	EntityMoveComp& operator=(EntityMoveComp&& other) = delete;

	void Initialize() override;
	void Update() override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

private:
	void FindLadder();
	void FindPlatform();

	HitboxComp* m_pHitbox{ nullptr };
	float m_Reach{ 10.f };
	float m_MoveSpeed{ 100.f };

	//TODO: create platform comp and ladder comp
	GameObject* m_pPlatform{ nullptr };
	GameObject* m_pLadder{ nullptr };
};

