#include "EnginePCH.h"
#include "Component.h"

int Component::idxCount = 0;

Component::Component()
	:m_Idx{idxCount}
{
	idxCount++;
}

GameObject* Component::GetGameObj() const
{
	if (!m_pGameObj)
		Logger::GetInstance().LogWarning("Component::GetGameObj(), component is not attached to any game object");

	return m_pGameObj;
}
