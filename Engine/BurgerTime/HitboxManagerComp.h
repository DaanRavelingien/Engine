#pragma once
#include "Component.h"

class HitboxComp;

class HitboxManagerComp : public Component
{
public:
	enum class CollisionGroup
	{
		CollisionGroup1 = 0b0001,
		CollisionGroup2 = 0b0010,
		CollisionGroup3 = 0b0100,
		CollisionGroup4 = 0b1000
	};

	HitboxManagerComp();
	~HitboxManagerComp();
	HitboxManagerComp(const HitboxManagerComp& other) = delete;
	HitboxManagerComp(HitboxManagerComp&& other) = delete;
	HitboxManagerComp& operator=(const HitboxManagerComp& other) = delete;
	HitboxManagerComp& operator=(HitboxManagerComp&& other) = delete;

	void Update() override;

	bool AreOverlapping(const glm::vec4& hitbox1, const glm::vec4& hitbox2);
	void AddHitbox(HitboxComp* pHitbox);
	void RemoveHitbox(HitboxComp* pHitbox);

private:
	std::vector<HitboxComp*> m_Hitboxes{};

};

