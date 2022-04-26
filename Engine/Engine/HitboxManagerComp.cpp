#include "EnginePCH.h"
#include "HitboxManagerComp.h"
#include "GameObject.h"

//component includes
#include "HitboxComp.h"
#include "TransformComp.h"

HitboxManagerComp::HitboxManagerComp()
	:Component{typeid(this).name()}
{}

void HitboxManagerComp::Update()
{
	//removing deleted hitboxes and clearing the overlapping hitboxes
	auto it = std::remove_if(m_Hitboxes.begin(), m_Hitboxes.end(), [](HitboxComp* pHitbox)
		{
			if (pHitbox && !pHitbox->GetGameObj()->IsDestroyed())
			{
				pHitbox->ClearOverlappingHitboxes();
				return false;
			}
			return true;
		});
	if(it != m_Hitboxes.end())
		m_Hitboxes.erase(it, m_Hitboxes.end());

	//comparing the hitboxes to each other to update wich ones overlap
	for (int i{}; i<(int)m_Hitboxes.size(); i++)
	{
		if (!m_Hitboxes.at(i))
			continue;

		glm::vec3 thisPos{ m_Hitboxes.at(i)->GetGameObj()->GetTransform()->GetPos() };
		glm::vec2 thistSize{ m_Hitboxes.at(i)->GetSize() };
		glm::vec4 thisHitboxRect{ thisPos.x,thisPos.y,thistSize.x,thistSize.y };

		for (int j{i+1}; j<(int)m_Hitboxes.size(); j++)
		{
			if (!m_Hitboxes.at(j))
				continue;

			//checking if the collision groups ar ok
			if ((int(m_Hitboxes.at(i)->GetCollisionGroup()) & int(m_Hitboxes.at(j)->GetCollisionGroup())) == 0)
				continue;

			glm::vec3 otherPos{ m_Hitboxes.at(j)->GetGameObj()->GetTransform()->GetPos() };
			glm::vec2 otherSize{ m_Hitboxes.at(j)->GetSize() };
			glm::vec4 otherHitboxRect{ otherPos.x,otherPos.y,otherSize.x,otherSize.y };

			if (AreOverlapping(thisHitboxRect, otherHitboxRect))
			{
				//adding to eachothers list
				m_Hitboxes.at(i)->AddOverlappingHitBox(m_Hitboxes.at(j));
				m_Hitboxes.at(j)->AddOverlappingHitBox(m_Hitboxes.at(i));
			}
		}
	}
	
}

bool HitboxManagerComp::AreOverlapping(const glm::vec4& hitbox1, const glm::vec4& hitbox2)
{
	//checking if ether rectangle is on the left of the other
	if (hitbox1.x > hitbox2.x + hitbox2.z || hitbox2.x > hitbox1.x + hitbox1.z)
		return false;

	//checking if ether rectangle is above the other
	if (hitbox1.y > hitbox2.y + hitbox2.w || hitbox2.y > hitbox1.y + hitbox1.w)
		return false;

	return true;
}

void HitboxManagerComp::AddHitbox(HitboxComp* pHitbox)
{
	m_Hitboxes.emplace_back(pHitbox);
}
