#pragma once
#include "Component.h"
#include "glm\detail\type_vec2.hpp"
#include <vector>
#include "HitboxManagerComp.h"

enum class HitboxTag
{
	Player,
	Platform,
	Ladder,
	Enemy,
	Tray,
	Ingredient,
	ingredientPiece
};

class HitboxComp : public Component
{
public:
	HitboxComp(HitboxTag tag, float width, float height, HitboxManagerComp::CollisionGroup collisionGroup = HitboxManagerComp::CollisionGroup::CollisionGroup1);
	~HitboxComp() = default;
	HitboxComp(const HitboxComp& other) = delete;
	HitboxComp(HitboxComp&& other) = delete;
	HitboxComp& operator=(const HitboxComp& other) = delete;
	HitboxComp& operator=(HitboxComp&& other) = delete;

	void Initialize() override;

	void AddOverlappingHitBox(HitboxComp* pOtherHitbox) { m_OverlappingHitboxes.push_back(pOtherHitbox); };
	void ClearOverlappingHitboxes() { m_OverlappingHitboxes.clear(); };
	std::vector<HitboxComp*> GetOverlappingHitboxes() const { return m_OverlappingHitboxes; };
	glm::vec2 GetSize() const;
	HitboxTag GetTag() const { return m_Tag; };

	HitboxManagerComp::CollisionGroup GetCollisionGroup() const { return m_CollisionGroups; };

private:
	glm::vec2 m_HitboxSize{};
	std::vector<HitboxComp*> m_OverlappingHitboxes{};
	HitboxTag m_Tag{};
	HitboxManagerComp::CollisionGroup m_CollisionGroups{};

	bool m_IsOvelapping{ false };
};

