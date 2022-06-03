#include "EnginePCH.h"
#include "HitboxComp.h"
#include "GameObject.h"
#include "BurgerTimeLvl.h"

//component includes
#include "TransformComp.h"

HitboxComp::HitboxComp(HitboxTag tag, float width, float height, HitboxManagerComp::CollisionGroup collisionGroup)
	:Component{typeid(this).name()}
	,m_HitboxSize{width,height}
	,m_Tag{tag}
	,m_CollisionGroups{collisionGroup}
{}

HitboxComp::~HitboxComp()
{
	if (m_pManager)
		m_pManager->RemoveHitbox(this);
}

void HitboxComp::Initialize()
{
	//adding the new hitbox to the hitboxManager
	m_pManager = dynamic_cast<BurgerTimeLvl*>(m_pGameObj->GetScene())->GetHitboxManager()->GetComponent<HitboxManagerComp>();
	m_pManager->AddHitbox(this);
}

glm::vec2 HitboxComp::GetSize() const
{
	glm::vec2 size{ m_HitboxSize };
	size.x *= m_pGameObj->GetTransform()->GetScale().x;
	size.y *= m_pGameObj->GetTransform()->GetScale().y;

	return size;
}
