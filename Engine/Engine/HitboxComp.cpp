#include "EnginePCH.h"
#include "HitboxComp.h"
#include "GameObject.h"
#include "Scene.h"

//component includes
#include "TransformComp.h"
#include "HitboxManagerComp.h"

HitboxComp::HitboxComp(HitboxManagerComp* pHitboxmanager, float width, float height)
	:Component{typeid(this).name()}
	,m_HitboxSize{width,height}
	,m_pHitboxManager{pHitboxmanager}
{}

void HitboxComp::Initialize()
{
	//adding the new hitbox to the hitboxManager
	m_pHitboxManager->AddHitbox(this);
}

bool HitboxComp::IsOverlapping(HitboxComp* other)
{
	glm::vec4 otherHitbox{ other->GetGameObj()->GetTransform()->GetPos().x, other->GetGameObj()->GetTransform()->GetPos().y,
		other->GetSize().x, other->GetSize().y };
	glm::vec4 thisHitbox{ m_pGameObj->GetTransform()->GetPos().x, m_pGameObj->GetTransform()->GetPos().y,
		m_HitboxSize.x,m_HitboxSize.y };
	
	//checking if ether rectangle is on the left of the other
	if (thisHitbox.x > otherHitbox.x + otherHitbox.z || otherHitbox.x > thisHitbox.x + thisHitbox.z)
		return false;

	//checking if ether rectangle is above the other
	if (thisHitbox.y > otherHitbox.y + otherHitbox.w || otherHitbox.y > thisHitbox.y + thisHitbox.w)
		return false;

	m_OverlappingHitboxes.push_back(other);
	return true;
}
