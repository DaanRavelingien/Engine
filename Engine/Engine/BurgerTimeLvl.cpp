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
#include "TextComp.h"
#include "ScoreCounterComp.h"
#include "ScoreInpComp.h"

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
	pLivesDisplay->GetTransform()->SetPos({ 20,700,0 });
	m_pHud->AddChild(pLivesDisplay);

	GameObject* pScoreDisplay(new GameObject{ "ScoreDisplay" });
	GameObject* pScoreLabel{ new GameObject{ "ScoreLabel" } };
	pScoreLabel->AddComponent(new Render2DComp{});
	pScoreLabel->AddComponent(new TextComp{ "SCORE", "Fonts/ARCADECLASSIC.otf", 50,{1,0,0} });
	pScoreLabel->GetTransform()->SetPos({ 0,0,0 });
	pScoreDisplay->AddChild(pScoreLabel);

	GameObject* pScoreCount{ new GameObject{"ScoreCount"} };
	pScoreCount->AddComponent(new Render2DComp);
	pScoreCount->AddComponent(new TextComp{ "0", "Fonts/ARCADECLASSIC.otf", 50, {1,1,1} });
	pScoreCount->AddComponent(new ScoreCounterComp{});
	pScoreCount->AddComponent(new ScoreInpComp{});
	pScoreCount->GetTransform()->SetPos({ 0,40,0 });
	pScoreDisplay->AddChild(pScoreCount);

	pScoreDisplay->GetTransform()->SetPos({ 20,10,0 });
	m_pHud->AddChild(pScoreDisplay);

	AddGameObj(m_pHud);

}
