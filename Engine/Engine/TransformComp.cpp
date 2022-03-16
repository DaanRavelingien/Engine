#include "EnginePCH.h"
#include "TransformComp.h"
#include "GameObject.h"

glm::vec3 TransformComp::GetPos() const
{
	//keeping into account the transform of the parent
	if(m_pGameObj->GetParent())
		return m_pGameObj->GetParent()->GetTransform()->GetPos() + m_Position;
	return m_Position;
}

void TransformComp::SetPos(const glm::vec3& pos)
{
	m_Position = pos;
	m_pGameObj->SendNotification(this, Event::COMPONENT_TRANSFORM_MOVED);
}

glm::vec3 TransformComp::GetScale() const
{
	//keeping into account the transform of the parent
	if (m_pGameObj->GetParent())
		return m_pGameObj->GetParent()->GetTransform()->GetScale() * m_Scale;
	return m_Scale;
}

void TransformComp::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
	m_pGameObj->SendNotification(this, Event::COMPONENT_TRANSFORM_SCALED);
}

glm::vec3 TransformComp::GetRotation() const
{
	//keeping into account the transform of the parent
	if (m_pGameObj->GetParent())
		return m_pGameObj->GetParent()->GetTransform()->GetRotation() + m_Rotation;
	return m_Rotation;
}

void TransformComp::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
	m_pGameObj->SendNotification(this, Event::COMPONENT_TRANSFORM_ROTATED);
}

