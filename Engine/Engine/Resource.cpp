#include "EnginePCH.h"
#include "Resource.h"

int Resource::m_ResourceCounter{ 0 };

Resource::Resource(const std::string& name)
	:m_Name{name}
	, m_Idx{m_ResourceCounter}
{
	++m_ResourceCounter;
}
