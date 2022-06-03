#include "EnginePCH.h"
#include "MenuComp.h"
#include "GameObject.h"
#include "MenuSelectionComp.h"
#include "TextureComp.h"
#include "TransformComp.h"

MenuComp::MenuComp()
	:Component{typeid(this).name()}
{
}

void MenuComp::Initialize()
{
	UpdateMenuPointer();
}

void MenuComp::SelectNext()
{
	//deselect the old option
	MenuSelectionComp* pSelection{};
	pSelection = m_pGameObj->GetChildren().at(m_SelectedOption)->GetComponent<MenuSelectionComp>();
	if(pSelection)
		pSelection->Deselect();

	m_SelectedOption++;

	if (m_SelectedOption == (int)m_pGameObj->GetChildren().size())
		m_SelectedOption = 0;

	//select the new option
	pSelection = m_pGameObj->GetChildren().at(m_SelectedOption)->GetComponent<MenuSelectionComp>();
	if(pSelection)
		pSelection->Select();

	UpdateMenuPointer();
}

void MenuComp::SelectPrev()
{
	//deselect the old option
	MenuSelectionComp* pSelection{};
	pSelection = m_pGameObj->GetChildren().at(m_SelectedOption)->GetComponent<MenuSelectionComp>();
	if(pSelection)
		pSelection->Deselect();

	m_SelectedOption--;

	if (m_SelectedOption < 0)
		m_SelectedOption = (int)m_pGameObj->GetChildren().size() - 1;

	//select the new option
	pSelection = m_pGameObj->GetChildren().at(m_SelectedOption)->GetComponent<MenuSelectionComp>();
	if(pSelection)
		pSelection->Select();

	UpdateMenuPointer();
}

void MenuComp::Select()
{
	MenuSelectionComp* pSelection{};

	pSelection = m_pGameObj->GetChildren().at(m_SelectedOption)->GetComponent<MenuSelectionComp>();

	if (pSelection)
		pSelection->Activate();
	else
		LOGERROR("no selection component was found in a child of the menu");
}

void MenuComp::UpdateMenuPointer()
{
	TextureComp* pPointerTexture{ m_pGameObj->GetComponent<TextureComp>() };

	//check if we have a pointer texture if not just dont do anything
	//means we have a menu without pointer
	if (pPointerTexture)
	{
		glm::vec3 newPointerPos{ m_pGameObj->GetChildren().at(m_SelectedOption)->GetTransform()->GetPos()
			- m_pGameObj->GetTransform()->GetPos() };
		newPointerPos += m_MenuPointerOffset;		

		glm::vec2 destRectSize{ pPointerTexture->GetDestRect().z,pPointerTexture->GetDestRect().w };

		pPointerTexture->SetDestRect({ newPointerPos.x,newPointerPos.y, destRectSize.x,destRectSize.y });
	}

}
