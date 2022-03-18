#include "EnginePCH.h"
#include "BurgerTimeLvl.h"
#include "GameObject.h"
#include "glm\detail\type_vec4.hpp"
#include "ResourceManager.h"
#include "InputManager.h"

//component includes
#include "TextureComp.h"
#include "TransformComp.h"
#include "LivesDisplayComp.h"
#include "HealthComp.h"
#include "DamageInpComp.h"
#include "TextComp.h"
#include "ScoreCounterComp.h"
#include "ScoreInpComp.h"
#include "TextRenderComp.h"
#include "TextureRenderComp.h"
#include "SteamAchivementsComp.h"

void BurgerTimeLvl::Initialize()
{
	//saying to inputManager we expect 2 controllers
	InputManager::GetInstance().SetControllerAmount(2);

	//loading the burgertime texture with all the sprites
	int burgerTimeTextureIdx = ResourceManager::GetInstance().LoadTexture("Textures/BurgerTimeSprites.png");

	//create the achievement manager for steam achievements
	//=====================================================
	GameObject* pSteamAchievementManager{ new GameObject{"AchievementManager"} };
	pSteamAchievementManager->AddComponent(new SteamAchivementsComp{ this });
	AddGameObj(pSteamAchievementManager);

	//creating peterPepper
	//====================
	m_pPeterPepper = new GameObject{ "PeterPepper" };
	m_pPeterPepper->AddComponent(new TextureRenderComp{});

	TextureComp* pPeterPepperTextureComp{ new TextureComp{burgerTimeTextureIdx} };
	pPeterPepperTextureComp->SetSourceRect({ 16,0,16,16 });
	pPeterPepperTextureComp->SetDestRect({ 16,16,16,16 });
	m_pPeterPepper->AddComponent(pPeterPepperTextureComp);
	m_pPeterPepper->AddComponent(new HealthComp{ 5 });
	m_pPeterPepper->AddComponent(new DamageInpComp{Controller::Controller_1});

	m_pPeterPepper->GetTransform()->SetPos({ 270,250,0 });
	m_pPeterPepper->GetTransform()->SetScale({ 3,3,3 });
	AddGameObj(m_pPeterPepper);

	//creating second player
	//======================
	m_pSallySalt = new GameObject{ "SallySalt" };
	m_pSallySalt->AddComponent(new TextureRenderComp{});

	pPeterPepperTextureComp = new TextureComp{burgerTimeTextureIdx};
	pPeterPepperTextureComp->SetSourceRect({ 16,0,16,16 });
	pPeterPepperTextureComp->SetDestRect({ 16,16,16,16 });
	m_pSallySalt->AddComponent(pPeterPepperTextureComp);
	m_pSallySalt->AddComponent(new HealthComp{ 5 });
	m_pSallySalt->AddComponent(new DamageInpComp{ Controller::Controller_2 });

	m_pSallySalt->GetTransform()->SetPos({ 350,250,0 });
	m_pSallySalt->GetTransform()->SetScale({ 3,3,3 });
	AddGameObj(m_pSallySalt);

	//creating hud
	//============
	m_pHud = new GameObject{ "Hud" };
	//creating the display for the lives and score of player 1
	GameObject* pLivesDisplay{ new GameObject{"LivesDisplay"} };
	pLivesDisplay->AddComponent(new LivesDisplayComp(m_pPeterPepper, burgerTimeTextureIdx));
	pLivesDisplay->GetTransform()->SetScale({ 3,3,3 });
	pLivesDisplay->GetTransform()->SetPos({ 20,700,0 });
	m_pHud->AddChild(pLivesDisplay);

	GameObject* pScoreDisplay{ new GameObject{ "ScoreDisplay" } };
	GameObject* pScoreLabel{ new GameObject{ "ScoreLabel" } };
	pScoreLabel->AddComponent(new TextRenderComp{});
	pScoreLabel->AddComponent(new TextComp{ "SCORE P1", "Fonts/ARCADECLASSIC.otf", 50,{1,0,0} });
	pScoreLabel->GetTransform()->SetPos({ 0,0,0 });
	pScoreDisplay->AddChild(pScoreLabel);

	GameObject* pScoreCount{ new GameObject{"ScoreCount"} };
	pScoreCount->AddComponent(new TextRenderComp);
	pScoreCount->AddComponent(new TextComp{ "0", "Fonts/ARCADECLASSIC.otf", 50, {1,1,1} });
	pScoreCount->AddComponent(new ScoreCounterComp{});
	pScoreCount->AddComponent(new ScoreInpComp{Controller::Controller_1});
	pScoreCount->GetTransform()->SetPos({ 0,40,0 });
	pScoreDisplay->AddChild(pScoreCount);

	pScoreDisplay->GetTransform()->SetPos({ 20,10,0 });
	m_pHud->AddChild(pScoreDisplay);

	//creating the display for the lives and score of player 2
	pLivesDisplay = new GameObject{ "LivesDisplayP1" };
	pLivesDisplay->AddComponent(new LivesDisplayComp(m_pSallySalt, burgerTimeTextureIdx));
	pLivesDisplay->GetTransform()->SetScale({ 3,3,3 });
	pLivesDisplay->GetTransform()->SetPos({ 672,700,0 });
	m_pHud->AddChild(pLivesDisplay);

	pScoreDisplay = new GameObject{ "ScoreDisplayP1" };
	pScoreLabel = new GameObject{ "ScoreLabelP1" };
	pScoreLabel->AddComponent(new TextRenderComp{});
	pScoreLabel->AddComponent(new TextComp{ "SCORE P2", "Fonts/ARCADECLASSIC.otf", 50,{0,1,0} });
	pScoreLabel->GetTransform()->SetPos({ 0,0,0 });
	pScoreDisplay->AddChild(pScoreLabel);

	pScoreCount = new GameObject{ "ScoreCountP1" };
	pScoreCount->AddComponent(new TextRenderComp);
	pScoreCount->AddComponent(new TextComp{ "0", "Fonts/ARCADECLASSIC.otf", 50, {1,1,1} });
	pScoreCount->AddComponent(new ScoreCounterComp{});
	pScoreCount->AddComponent(new ScoreInpComp{ Controller::Controller_2 });
	pScoreCount->GetTransform()->SetPos({ 0,40,0 });
	pScoreDisplay->AddChild(pScoreCount);

	pScoreDisplay->GetTransform()->SetPos({ 500,10,0 });
	m_pHud->AddChild(pScoreDisplay);

	AddGameObj(m_pHud);

}
