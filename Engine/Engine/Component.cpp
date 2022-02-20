#include "EnginePCH.h"
#include "Component.h"

int Component::m_IdxCount = 0;
std::vector<std::string> Component::m_ComponentTypes{};

Component::Component(const std::string& compName)
	:m_Idx{m_IdxCount}
	, m_CompName{}
{
	m_IdxCount++;

	//simplifying the comp name
	std::string simpleCompType{ SimplifyCompTypeName(compName) };
	m_CompName = simpleCompType;

	//add the type to the list if its not already in there
	auto it = std::find_if(m_ComponentTypes.begin(), m_ComponentTypes.end(), [simpleCompType](const std::string& compType)
		{
			if (simpleCompType.compare(compType) == 0)
				return true;
			return false;
		});
	//if the added component was new we add it to the list
	if (it == m_ComponentTypes.end())
		m_ComponentTypes.push_back(simpleCompType);

}

GameObject* Component::GetGameObj() const
{
	if (!m_pGameObj)
		LOGWARNING("component is not attached to any game object");

	return m_pGameObj;
}

std::string Component::SimplifyCompTypeName(const std::string& compTypeName)
{
	//simplifying the comp name, now it should come in in the format below
	//example: "class TransformComp * __ptr64"
	//we only want to keep the "TransformComp" part

	//first we check if the 1st word we encounter is "class"
	std::string classString{ compTypeName.substr(0,compTypeName.find(' ')) };
	if (classString.compare("class") != 0)
	{
		LOGERROR("Expected a different format for the component type name, found: " + classString + " but expected: class");
		return "ERROR_TYPE";
	}

	//getting the next first word wich should be the simpeler version we want
	std::string simpleCompType{ compTypeName };

	//removing class from the string
	simpleCompType.erase(0, simpleCompType.find(' ') + 1);
	//removing the remaining characters at the end we dont need(" * __ptr64")
	simpleCompType.erase(simpleCompType.find(' '), simpleCompType.size());

	return simpleCompType;
}
