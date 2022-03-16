#include "BurgerTimeLvl.h"
#include "GameObject.h"
#include "glm\detail\type_vec4.hpp"
#include "ResourceManager.h"

//component includes
#include "TextureComp.h"
#include "TransformComp.h"
#include "Render2DComp.h"
#include "LivesDisplayComp.h"
#include "HealthComp.h"
#include "DamageInpComp.h"

void BurgerTimeLvl::Initialize()
{
	//loading the burgertime texture with all the sprites
	int burgerTimeTextureIdx = ResourceManager::GetInstance().LoadTexture("Textures/BurgerTimeSprites.png");

	//creating peterPepper
	m_pPeterPepper = new GameObject{ "PeterPepper" };
	m_pPeterPepper->AddComponent(new Render2DComp{});

	TextureComp* pPeterPepperTextureComp{ new TextureComp{burgerTimeTextureIdx} };
	pPeterPepperTextureComp->SetSourceRect({ 16,0,16,16 });
	pPeterPepperTextureComp->SetDestRect({ 16,16,16,16 });
	m_pPeterPepper->AddComponent(pPeterPepperTextureComp);
	m_pPeterPepper->AddComponent(new HealthComp{ 5 });
	m_pPeterPepper->AddComponent(new DamageInpComp{});

	m_pPeterPepper->GetTransform()->SetPos({ 270,250,0 });
	m_pPeterPepper->GetTransform()->SetScale({ 3,3,3 });
	AddGameObj(m_pPeterPepper);

	//creating hud
	m_pHud = new GameObject{ "Hud" };
	//creating the display for the lives
	GameObject* pLivesDisplay{ new GameObject{"LivesDisplay"} };
	pLivesDisplay->AddComponent(new LivesDisplayComp(m_pPeterPepper, burgerTimeTextureIdx));
	pLivesDisplay->GetTransform()->SetScale({ 3,3,3 });
	m_pHud->AddChild(pLivesDisplay);

	GameObject* pScoreDisplay(new GameObject{ "ScoreDisplay" });


	m_pHud->AddChild(pScoreDisplay);

	m_pHud->GetTransform()->SetPos({ 20,700,0 });
	AddGameObj(m_pHud);

}

void BurgerTimeLvl::Update()
{


}
