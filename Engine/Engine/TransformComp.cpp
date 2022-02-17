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

glm::vec3 TransformComp::GetScale() const
{
	//keeping into account the transform of the parent
	if (m_pGameObj->GetParent())
		return m_pGameObj->GetParent()->GetTransform()->GetScale() + m_Scale;
	return m_Scale;
}

glm::vec3 TransformComp::GetRotation() const
{
	//keeping into account the transform of the parent
	if (m_pGameObj->GetParent())
		return m_pGameObj->GetParent()->GetTransform()->GetRotation() + m_Rotation;
	return m_Rotation;
}

