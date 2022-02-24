#include "EnginePCH.h"
#include "Resource.h"

int Resource::m_ResourceCounter{ 0 };

Resource::Resource()
	:m_Idx{m_ResourceCounter}
{
	++m_ResourceCounter;
}

Resource::Resource(int idx)
	:m_Idx{idx}
{

}
