#pragma once
#include "Component.h"
#include "glm\detail\type_vec2.hpp"
#include <vector>

class HitboxManagerComp;

class HitboxComp : public Component
{
public:
	HitboxComp(HitboxManagerComp* pHitboxmanager, float width, float height);
	~HitboxComp() = default;
	HitboxComp(const HitboxComp& other) = delete;
	HitboxComp(HitboxComp&& other) = delete;
	HitboxComp& operator=(const HitboxComp& other) = delete;
	HitboxComp& operator=(HitboxComp&& other) = delete;

	void Initialize() override;

	bool IsOverlapping(HitboxComp* other);
	void ClearOverlappingHitboxes() { m_OverlappingHitboxes.clear(); };
	std::vector<HitboxComp*> GetOverlappingHitboxes() const { return m_OverlappingHitboxes; };
	glm::vec2 GetSize() const;

private:
	glm::vec2 m_HitboxSize{};
	std::vector<HitboxComp*> m_OverlappingHitboxes{};
	HitboxManagerComp* m_pHitboxManager{ nullptr };

	bool m_IsOvelapping{ false };
};

