#include "EnginePCH.h"
#include "MenuPointerComp.h"
#include "GameObject.h"

//component includes
#include "TransformComp.h"

MenuPointerComp::MenuPointerComp()
	:Component{typeid(this).name()}
{
}

void MenuPointerComp::Initialize()
{
	//getting the different positions from the child objects of the menu
	for (GameObject* pObj : m_pGameObj->GetParent()->GetChildren())
	{
		//checking so we dont take this obj
		if (m_pGameObj == pObj)
			continue;

		m_Positions.push_back(pObj->GetTransform()->GetPos() - m_pGameObj->GetParent()->GetTransform()->GetPos());
	}

	//setting the pointer to the first position
	m_PointerPos = 0;
	m_pGameObj->GetTransform()->SetPos(m_Positions.at(m_PointerPos) + m_Offset);
}

void MenuPointerComp::MovePointerUp()
{
	m_PointerPos--;
	if (m_PointerPos < 0)
		m_PointerPos = int(m_Positions.size() - 1);

	m_pGameObj->GetTransform()->SetPos(m_Positions.at(m_PointerPos) + m_Offset);
}

void MenuPointerComp::MovePointerDown()
{

	m_PointerPos++;
	if (m_PointerPos == (int)m_Positions.size())
		m_PointerPos = 0;

	m_pGameObj->GetTransform()->SetPos(m_Positions.at(m_PointerPos) + m_Offset);
}
