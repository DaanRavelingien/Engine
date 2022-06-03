#include "EnginePCH.h"
#include "EntityMoveComp.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Scene.h"

//component includes
#include "TransformComp.h"
#include "HitboxComp.h"

EntityMoveComp::EntityMoveComp(const glm::vec2& spawnPosition)
	:Component{typeid(this).name()}
	,m_spawnPos{spawnPosition}
{
}

void EntityMoveComp::Initialize()
{
	m_pHitbox = m_pGameObj->GetComponent<HitboxComp>();
	if (!m_pHitbox)
		LOGWARNING("could not find a hitbox component");

	//adding this as an observer to the scene
	m_pGameObj->GetScene()->AddObserver(this);

	Respawn();

	//clamping the position of the object to the size of the start platform
	if (m_pPlatform)
	{
		glm::vec3 currentPos{ m_pGameObj->GetTransform()->GetPos() };
		glm::vec3 platformPos{ m_pPlatform->GetTransform()->GetPos() };

		//setting the object on top of the platform
		m_pGameObj->GetTransform()->SetPos({ currentPos.x,platformPos.y,currentPos.z });
		currentPos = m_pGameObj->GetTransform()->GetPos();

		//clamping the pos to the lenght of the platform
		if (m_pGameObj->GetTransform()->GetPos().x < platformPos.x)
			m_pGameObj->GetTransform()->SetPos({ platformPos.x,currentPos.y,currentPos.z });

		float right{ m_pPlatform->GetTransform()->GetPos().x + m_pPlatform->GetComponent<HitboxComp>()->GetSize().x
			- m_pGameObj->GetComponent<HitboxComp>()->GetSize().x };
		if (m_pGameObj->GetTransform()->GetPos().x > right)
			m_pGameObj->GetTransform()->SetPos({ right, currentPos.y ,currentPos.z });
	}
}

void EntityMoveComp::Update()
{
	//setting a platform or ladder if we dont have one
	//mainly for the start of the game so we just can place entities on platforms to spawn them
	if (!m_pPlatform && !m_pLadder)
	{
		FindPlatform();
		if(!m_pPlatform)
			FindLadder();
	}

	glm::vec3 currentPos{ m_pGameObj->GetTransform()->GetPos() };

	//allign to the floor or ladder you are currently on
	if (m_pLadder)
		m_pGameObj->GetTransform()->SetPos({ m_pLadder->GetTransform()->GetPos().x, currentPos.y, currentPos.z });

	if (m_pPlatform)
		m_pGameObj->GetTransform()->SetPos({ currentPos.x, m_pPlatform->GetTransform()->GetPos().y, currentPos.z });
}

void EntityMoveComp::Respawn()
{
	m_pPlatform = nullptr;
	m_pLadder = nullptr;

	m_pGameObj->GetTransform()->SetPos(glm::vec3{ m_spawnPos.x,m_spawnPos.y,m_pGameObj->GetTransform()->GetPos().z });
}

void EntityMoveComp::MoveUp()
{
	//checking if we need to find a ladder
	if (!m_pLadder)
	{
		FindLadder();
	}

	//adding the movement if there was a ladder close by
	if (m_pLadder)
	{
		//disabeling the platform movement
		m_pPlatform = nullptr;

		glm::vec3 currentPos{ m_pGameObj->GetTransform()->GetPos() };
		glm::vec3 ladderPos{ m_pLadder->GetTransform()->GetPos() };

		float newYPos{ currentPos.y - m_MoveSpeed * GameTime::GetInstance().GetDeltaTime() };

		m_pGameObj->GetTransform()->SetPos({ currentPos.x,newYPos,currentPos.z });

		//clamping the pos to the lenght of the ladder
		if (m_pGameObj->GetTransform()->GetPos().y < ladderPos.y)
			m_pGameObj->GetTransform()->SetPos({ currentPos.x,ladderPos.y,currentPos.z });

		float top{ m_pLadder->GetTransform()->GetPos().y + m_pLadder->GetComponent<HitboxComp>()->GetSize().y };
		if (m_pGameObj->GetTransform()->GetPos().y > top)
			m_pGameObj->GetTransform()->SetPos({ currentPos.x,top,currentPos.z });
	}
}

void EntityMoveComp::MoveDown()
{
	//checking if we need to find a ladder
	if (!m_pLadder)
	{
		FindLadder();
	}

	//adding the movement if there was a ladder close by
	if (m_pLadder)
	{
		//disabeling the platform movement
		m_pPlatform = nullptr;

		glm::vec3 currentPos{ m_pGameObj->GetTransform()->GetPos() };
		glm::vec3 ladderPos{ m_pLadder->GetTransform()->GetPos() };

		float newYPos{ currentPos.y + m_MoveSpeed * GameTime::GetInstance().GetDeltaTime() };

		m_pGameObj->GetTransform()->SetPos({ currentPos.x,newYPos,currentPos.z });

		//clamping the pos to the lenght of the ladder
		if (m_pGameObj->GetTransform()->GetPos().y < ladderPos.y)
			m_pGameObj->GetTransform()->SetPos({ currentPos.x,ladderPos.y,currentPos.z });

		float top{ m_pLadder->GetTransform()->GetPos().y + m_pLadder->GetComponent<HitboxComp>()->GetSize().y };
		if (m_pGameObj->GetTransform()->GetPos().y > top)
			m_pGameObj->GetTransform()->SetPos({ currentPos.x,top,currentPos.z });
	}
}

void EntityMoveComp::MoveLeft()
{
	//checking if we need to find a platform
	if (!m_pPlatform)
	{
		FindPlatform();
	}

	//handeling movement if we are on a platform
	if (m_pPlatform)
	{
		//disabeling movement on ladders
		m_pLadder = nullptr;

		glm::vec3 currentPos{ m_pGameObj->GetTransform()->GetPos() };
		glm::vec3 platformPos{ m_pPlatform->GetTransform()->GetPos() };

		float newXPos{ currentPos.x - m_MoveSpeed * GameTime::GetInstance().GetDeltaTime() };

		m_pGameObj->GetTransform()->SetPos({ newXPos,currentPos.y,currentPos.z });

		//clamping the pos to the lenght of the platform
		if (m_pGameObj->GetTransform()->GetPos().x < platformPos.x)
			m_pGameObj->GetTransform()->SetPos({ platformPos.x,currentPos.y,currentPos.z });

		float right{ m_pPlatform->GetTransform()->GetPos().x + m_pPlatform->GetComponent<HitboxComp>()->GetSize().x
			- m_pGameObj->GetComponent<HitboxComp>()->GetSize().x };
		if (m_pGameObj->GetTransform()->GetPos().x > right)
			m_pGameObj->GetTransform()->SetPos({ right, currentPos.y ,currentPos.z });

	}
}

void EntityMoveComp::MoveRight()
{
	//checking if we need to find a platform
	if (!m_pPlatform)
	{
		FindPlatform();
	}

	//handeling movement if we are on a platform
	if (m_pPlatform)
	{
		//disabeling movement on ladders
		m_pLadder = nullptr;

		glm::vec3 currentPos{ m_pGameObj->GetTransform()->GetPos() };
		glm::vec3 platformPos{ m_pPlatform->GetTransform()->GetPos() };

		float newXPos{ currentPos.x + m_MoveSpeed * GameTime::GetInstance().GetDeltaTime() };

		m_pGameObj->GetTransform()->SetPos({ newXPos,currentPos.y,currentPos.z });

		//clamping the pos to the lenght of the platform
		if (m_pGameObj->GetTransform()->GetPos().x < platformPos.x)
			m_pGameObj->GetTransform()->SetPos({ platformPos.x,currentPos.y,currentPos.z });

		float right{ m_pPlatform->GetTransform()->GetPos().x + m_pPlatform->GetComponent<HitboxComp>()->GetSize().x
			- m_pGameObj->GetComponent<HitboxComp>()->GetSize().x };
		if (m_pGameObj->GetTransform()->GetPos().x > right)
			m_pGameObj->GetTransform()->SetPos({ right, currentPos.y ,currentPos.z });

	}
}

void EntityMoveComp::FindLadder()
{
	//first checking if the ladder is close enought by checking if the hitboxes are overlapping
	std::vector<HitboxComp*> hitboxes{ m_pHitbox->GetOverlappingHitboxes() };
	if (hitboxes.size() > 0)
	{
		//going through overlapping hitboxes and looking for a ladder
		for (HitboxComp* pHitbox : hitboxes)
		{
			if (pHitbox->GetTag() == HitboxTag::Ladder)
			{
				//checking if the ladder is in reach of the being
				if (m_Reach > abs(m_pGameObj->GetTransform()->GetPos().x - pHitbox->GetGameObj()->GetTransform()->GetPos().x))
				{
					m_pLadder = pHitbox->GetGameObj();
					break;
				}
			}
		}
	}
}

void EntityMoveComp::FindPlatform()
{
	//first checking if the platform is close enought by checking if the hitboxes are overlapping
	std::vector<HitboxComp*> hitboxes{ m_pHitbox->GetOverlappingHitboxes() };
	if (hitboxes.size() > 0)
	{
		//going through overlapping hitboxes and looking for a platform
		for (HitboxComp* pHitbox : hitboxes)
		{
			if (pHitbox->GetTag() == HitboxTag::Platform)
			{
				//checking if the ladder is in reach of the being
				if (m_Reach > abs(m_pGameObj->GetTransform()->GetPos().y - pHitbox->GetGameObj()->GetTransform()->GetPos().y))
				{
					m_pPlatform = pHitbox->GetGameObj();
					break;
				}
			}
		}
	}
}

void EntityMoveComp::Notify(Component*, Event event)
{
	if (event == Event::BURGERS_COMPLETE)
	{
		Respawn();
	}
}

