#include "EnginePCH.h"
#include "GravityComp.h"
#include "GameObject.h"

//component includes
#include "TransformComp.h"

GravityComp::GravityComp()
	:Component{typeid(this).name()}
{
}

void GravityComp::Update()
{
	if (!m_Enabled)
		return;

	//in pixels per second
	float gravitySpeed{ 150 };
	float displacement{ gravitySpeed * GameTime::GetInstance().GetDeltaTime() };

	glm::vec3 newPos{ m_pGameObj->GetTransform()->GetPos() - m_pGameObj->GetParent()->GetTransform()->GetPos() };
	newPos.y += displacement;

	m_pGameObj->GetTransform()->SetPos(newPos);

}
