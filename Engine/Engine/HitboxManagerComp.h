#pragma once
#include "Component.h"
#include <vector>

class HitboxComp;

class HitboxManagerComp : Component
{
public:
	HitboxManagerComp();
	~HitboxManagerComp() = default;
	HitboxManagerComp(const HitboxManagerComp& other) = delete;
	HitboxManagerComp(HitboxManagerComp&& other) = delete;
	HitboxManagerComp& operator=(const HitboxManagerComp& other) = delete;
	HitboxManagerComp& operator=(HitboxManagerComp&& other) = delete;

	void Update() override;

	void AddHitbox(HitboxComp* pHitbox) { m_Hitboxes.push_back(pHitbox); };

private:
	std::vector<HitboxComp*> m_Hitboxes{};

};

