#include "EnginePCH.h"
#include "HotDogBehaviourComp.h"
#include <algorithm>
#include <GameObject.h>

//component includes
#include "TransformComp.h"
#include "EntityMoveComp.h"
#include "HitboxComp.h"

HotDogBehaviourComp::HotDogBehaviourComp()
	:Component{ typeid(this).name() }
{
}

void HotDogBehaviourComp::Initialize()
{
	//set the target to the closest we have
	SetClosestTarget();

}

void HotDogBehaviourComp::Update()
{
	if (m_Targets.empty())
		return;

	//finding the platform we are on if not already found
	if (!m_pOldPlatform)
	{
		for (HitboxComp* pOtherHitbox : GetGameObj()->GetComponent<HitboxComp>()->GetOverlappingHitboxes())
		{
			if (pOtherHitbox->GetTag() == HitboxTag::Platform)
			{
				m_pOldPlatform = pOtherHitbox;
				break;
			}
		}
	}
	//finding the ladder we are on if not already found
	if (!m_pOldLadder)
	{
		for (HitboxComp* pOtherHitbox : GetGameObj()->GetComponent<HitboxComp>()->GetOverlappingHitboxes())
		{
			if (pOtherHitbox->GetTag() == HitboxTag::Ladder)
			{
				m_pOldLadder = pOtherHitbox;
				break;
			}
		}
	}

	//going to the closest target
	SetClosestTarget();

	//we will firs priorotize going up a ladder as the Hotdog
	glm::vec3 targetPos{ m_Targets.at(m_TargetIdx)->GetTransform()->GetPos() };
	glm::vec3 ourPos{ GetGameObj()->GetTransform()->GetPos() };
	float epsilon{ 0.1f };

	//getting the desired direction based on the pos of our target
	MoveDirection desiredVerticalDir{MoveDirection::None};
	//check if we are close enough to the value of the target, if so set no desired velocity in that axis
	if (std::abs(ourPos.y - targetPos.y) < epsilon)
	{
		desiredVerticalDir = MoveDirection::None;
	}
	else if (ourPos.y > targetPos.y)
	{
		desiredVerticalDir = MoveDirection::Up;
	}
	else if (ourPos.y < targetPos.y)
	{
		desiredVerticalDir = MoveDirection::Down;
	}
	MoveDirection desiredHorizontalDir{MoveDirection::None};
	//check if we are close enough to the value of the target, if so set no desired velocity in that axis
	if (std::abs(ourPos.x - targetPos.x) < epsilon)
	{
		desiredHorizontalDir = MoveDirection::None;
	}
	else if (ourPos.x > targetPos.x)
	{
		desiredHorizontalDir = MoveDirection::Left;
	}
	else if (ourPos.x < targetPos.x)
	{
		desiredHorizontalDir = MoveDirection::Right;
	}


	EntityMoveComp* moveComp{ GetGameObj()->GetComponent<EntityMoveComp>() };

	if (!moveComp)
		return;

	switch (m_Direction)
	{
	case HotDogBehaviourComp::MoveDirection::Up:

		//while going up we can only try to move left or right not down
		if (desiredHorizontalDir == MoveDirection::Left && moveComp->MoveLeft() && EncounteredNewPlatform())
			m_Direction = MoveDirection::Left;
		else if (desiredHorizontalDir == MoveDirection::Right && moveComp->MoveRight() && EncounteredNewPlatform())
			m_Direction = MoveDirection::Right;
		else
			moveComp->MoveUp();

		break;
	case HotDogBehaviourComp::MoveDirection::Down:

		//while going down we can only try to move left or right not up
		if (desiredHorizontalDir == MoveDirection::Left && moveComp->MoveLeft() && EncounteredNewPlatform())
			m_Direction = MoveDirection::Left;
		else if (desiredHorizontalDir == MoveDirection::Right && moveComp->MoveRight() && EncounteredNewPlatform())
			m_Direction = MoveDirection::Right;
		else
			moveComp->MoveDown();

		break;
	case HotDogBehaviourComp::MoveDirection::Left:

		//if we ar moving left we will try to move in our desired direction exept right
		//because we can be moving left because right was not possible
		if (desiredVerticalDir == MoveDirection::Up && moveComp->MoveUp() && EncounteredNewLadder())
			m_Direction = MoveDirection::Up;
		else if (desiredVerticalDir == MoveDirection::Down && moveComp->MoveDown() && EncounteredNewLadder())
			m_Direction = MoveDirection::Down;
		else
			moveComp->MoveLeft();

		break;
	case HotDogBehaviourComp::MoveDirection::Right:

		//if we ar moving right we will try to move in our desired direction exept left
		//because we can be moving right because left was not possible
		if (desiredVerticalDir == MoveDirection::Up && moveComp->MoveUp() && EncounteredNewLadder())
			m_Direction = MoveDirection::Up;
		else if (desiredVerticalDir == MoveDirection::Down && moveComp->MoveDown() && EncounteredNewLadder())
			m_Direction = MoveDirection::Down;
		else
			moveComp->MoveRight();
		break;
	default:
		break;
	}
}

void HotDogBehaviourComp::Reset()
{
	m_pOldLadder = nullptr;
	m_pOldPlatform = nullptr;

	m_Direction = MoveDirection::Up;
}

void HotDogBehaviourComp::SetClosestTarget()
{
	if (m_Targets.empty())
		return;

	auto it = std::min_element(m_Targets.begin(), m_Targets.end(), [this](GameObject* pTarget1, GameObject* pTarget2)
		{
			glm::vec3 posThis{ this->GetGameObj()->GetTransform()->GetPos() };
			glm::vec3 posTarg1{ pTarget1->GetTransform()->GetPos() };
			glm::vec3 posTarg2{ pTarget2->GetTransform()->GetPos() };

			float distSq1{};
			distSq1 = ((posThis.x - posTarg1.x) * (posThis.x - posTarg1.x)) + ((posThis.y - posTarg1.y) * (posThis.y - posTarg1.y));
			float distSq2{};
			distSq2 = ((posThis.x - posTarg2.x) * (posThis.x - posTarg2.x)) + ((posThis.y - posTarg2.y) * (posThis.y - posTarg2.y));

			if (distSq1 < distSq2)
				return true;
			return false;

		});

	m_TargetIdx = int(it - m_Targets.begin());
}

bool HotDogBehaviourComp::EncounteredNewPlatform()
{
	bool encounteredPlatform{ false };
	HitboxComp* pOurHitbox{ GetGameObj()->GetComponent<HitboxComp>() };

	if (!pOurHitbox)
		return encounteredPlatform;

	//do not do this functions if we dont have an old platform
	if (!m_pOldPlatform)
		return encounteredPlatform;

	for (HitboxComp* pOtherHitbox : pOurHitbox->GetOverlappingHitboxes())
	{
		//skip the hitbox if its not a platform or if its our old platform
		if (pOtherHitbox->GetTag() != HitboxTag::Platform && pOtherHitbox == m_pOldPlatform)
			continue;

		//checking if the we have an other overlapping platform that is closer then our old platform
		glm::vec3 ourPos{ GetGameObj()->GetTransform()->GetPos() };
		glm::vec3 otherPos{ pOtherHitbox->GetGameObj()->GetTransform()->GetPos() };
		glm::vec3 oldPlatPos{ m_pOldPlatform->GetGameObj()->GetTransform()->GetPos() };

		float distNewPlatf{ std::abs(ourPos.y - otherPos.y) };
		float distOldPlatf{ std::abs(ourPos.y - oldPlatPos.y) };

		if (distNewPlatf < distOldPlatf)
		{
			m_pOldPlatform = pOtherHitbox;
			encounteredPlatform = true;
		}
	}
	
	return encounteredPlatform;
}

bool HotDogBehaviourComp::EncounteredNewLadder()
{
	bool encounteredLadder{ false };
	HitboxComp* pOurHitbox{ GetGameObj()->GetComponent<HitboxComp>() };

	if (!pOurHitbox)
		return encounteredLadder;

	//do not do this functions if we dont have an old ladder
	if (!m_pOldLadder)
		return encounteredLadder;

	for (HitboxComp* pOtherHitbox : pOurHitbox->GetOverlappingHitboxes())
	{
		//skip the hitbox if its not a ladder or if its our old ladder
		if (pOtherHitbox->GetTag() != HitboxTag::Ladder && pOtherHitbox == m_pOldLadder)
			continue;

		//checking if the we have an other overlapping platform that is closer then our old platform
		glm::vec3 ourPos{ GetGameObj()->GetTransform()->GetPos() };
		glm::vec3 otherPos{ pOtherHitbox->GetGameObj()->GetTransform()->GetPos() };
		glm::vec3 oldLadPos{ m_pOldLadder->GetGameObj()->GetTransform()->GetPos() };

		float distNewLad{ std::abs(ourPos.x - otherPos.x) };
		float distOldLad{ std::abs(ourPos.x - oldLadPos.x) };

		if (distNewLad < distOldLad)
		{
			m_pOldLadder = pOtherHitbox;
			encounteredLadder = true;
		}
	}

	return encounteredLadder;
}
