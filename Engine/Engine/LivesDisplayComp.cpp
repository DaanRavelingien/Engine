#include "EnginePCH.h"
#include "LivesDisplayComp.h"
#include "GameObject.h"
#include "Events.h"
#include "ResourceManager.h"

//comp includes
#include "TextureRenderComp.h"
#include "TextureComp.h"
#include "HealthComp.h"
#include "TransformComp.h"


LivesDisplayComp::LivesDisplayComp(GameObject* pObj, const std::string& liveTexturePath)
	:Component(typeid(this).name())
	,m_pPeterPepper{pObj}
{
	m_LivesTextureIdx = ResourceManager::GetInstance().LoadTexture(liveTexturePath);
}

LivesDisplayComp::LivesDisplayComp(GameObject* pObj, int livesTextureIdx)
	: Component(typeid(this).name())
	,m_pPeterPepper{pObj}
	,m_LivesTextureIdx{livesTextureIdx}
{
}

void LivesDisplayComp::Initialize()
{
	int maxLives = m_pPeterPepper->GetComponent<HealthComp>()->GetMaxHealth();

	//create the objects that will display the lives
	//just a simple object with a texture comp and a render comp
	for (int i{}; i < maxLives; i++)
	{
		int textureSize{ 8 };

		GameObject* pLiveObj{ new GameObject{"LiveTexObj_" + std::to_string(i)} };
		pLiveObj->AddComponent(new TextureRenderComp{});

		TextureComp* pTextureComp{ new TextureComp{ m_LivesTextureIdx } };
		pTextureComp->SetSourceRect({ 201,0,textureSize,textureSize });
		pTextureComp->SetDestRect({ 0,0,textureSize,textureSize });

		pLiveObj->AddComponent(pTextureComp);
		
		int yPos{ (textureSize * i * (int)m_pGameObj->GetTransform()->GetScale().y)
			+ textureSize * (int)m_pGameObj->GetTransform()->GetScale().y };

		pLiveObj->GetTransform()->SetPos({ 0,-(float)yPos,0 });
		m_pGameObj->AddChild(pLiveObj);
	}

	//subscribe to the game object with lives
	m_pPeterPepper->AddObserver(this);
}

void LivesDisplayComp::Notify(Component* pComp, Event event)
{
	if (event == Event::COMPONENT_HEALTH_CHANGED)
	{
		int currentLives{ static_cast<HealthComp*>(pComp)->GetHealth() };

		std::vector<GameObject*> textureObjs = m_pGameObj->GetChildren();
		
		//disable and enable the lives we need
		for (size_t i{}; i < textureObjs.size(); i++)
		{
			if ((int)i < currentLives)
				textureObjs.at(i)->Enable();
			else
				textureObjs.at(i)->Disable();
		}


	}
}
